#include "LR_Model.h"
#include "float.h"

LR_Model * init_model(Feature *feats, long predictor_count, bool has_intercept)
{
    LR_Model *model = (LR_Model *) malloc(sizeof(LR_Model));
    if (!model) {
        fprintf(stderr, "Memory allocation error for LR_Model\n");
        exit(1);
    }
    model->has_intercept = has_intercept;
    model->weight_count = predictor_count;
    model->weights = (data_row) malloc(sizeof(long double) * predictor_count);
    model->weight_names = (char **) malloc(sizeof(char *) * predictor_count);

    if (!model->weights || !model->weight_names) {
        fprintf(stderr, "Memory allocation error for weights or weight_names\n");
        exit(1);
    }
    // Initialize weights to zero.
    for (int i = 0; i < predictor_count; i++) {
        model->weights[i] = 0.0L;
    }
    
    if (has_intercept) {
        // First weight name is "Intercept"
        model->weight_names[0] = malloc(strlen("Intercept") + 1);
        if (!model->weight_names[0]) {
            fprintf(stderr, "Memory allocation error for intercept name\n");
            exit(1);
        }
        strcpy(model->weight_names[0], "Intercept");
        // Copy the remaining predictor names from feats.
        for (int i = 1; i < predictor_count; i++) {
            model->weight_names[i] = malloc(strlen(feats[i - 1].name) + 1);
            if (!model->weight_names[i]) {
                fprintf(stderr, "Memory allocation error for feature name %d\n", i);
                exit(1);
            }
            strcpy(model->weight_names[i], feats[i - 1].name);
        }
    } else {
        // Without an intercept, copy predictor names directly.
        for (int i = 0; i < predictor_count; i++) {
            model->weight_names[i] = malloc(strlen(feats[i].name) + 1);
            if (!model->weight_names[i]) {
                fprintf(stderr, "Memory allocation error for feature name %d\n", i);
                exit(1);
            }
            strcpy(model->weight_names[i], feats[i].name);
        }
    }
    
    return model;
}

void free_model(LR_Model *model) {
    if (model == NULL)
        return;
    
    // Free the weights array.
    free(model->weights);
    
    // Free each individual string in weight_names.
    if (model->weight_names) {
        for (int i = 0; i < model->weight_count; i++) {
            free(model->weight_names[i]);
        }
        free(model->weight_names);
    }
    
    // Finally, free the model structure itself.
    free(model);
}


LR_Model * train_model(Feature *feats, Output output, long feat_count, bool has_intercept)
{
    long datapoints = feats[0].data.size;
    
    // Total number of weights = predictor features plus intercept (if applicable).
    int predictor_count = feat_count + (has_intercept ? 1 : 0);
    
    // Initialize model using the correct number of weights.
    LR_Model *model = init_model(feats, predictor_count, has_intercept);
    
    /* --- Build design matrix X --- */
    // X has "datapoints" rows and "predictor_count" columns.
    Matrix X = empty_matr(datapoints, predictor_count);
    for (int i = 0; i < datapoints; i++) {
        int colIndex = 0;
        if (has_intercept) {
            // First column is intercept (all ones)
            X.data[i].data[0] = 1.0;
            colIndex = 1;
        }
        // Fill remaining columns with predictor data from feats.
        for (int j = 0; j < feat_count; j++) {
            X.data[i].data[colIndex] = feats[j].data.data[i];
            colIndex++;
        }
    }
    
    Vector y_source = output.data;
    
    // Compute weights using the normal equation: w = (X^T X)^(-1) X^T y
    Matrix X_T = t_matrix(&X);
    Matrix XTX = mul_matr(&X_T, &X);
    Matrix XTX_inv = inv_matr(&XTX);
    
    Matrix Y = empty_matr(y_source.size, 1);
    for (int i = 0; i < y_source.size; i++) {
        Y.data[i].data[0] = y_source.data[i];
    }
    
    Matrix XTy = mul_matr(&X_T, &Y);
    Matrix w_mat = mul_matr(&XTX_inv, &XTy);
    
    // Store the computed weights into the model.
    for (int i = 0; i < predictor_count; i++) {
        model->weights[i] = w_mat.data[i].data[0];
    }
    
    /* --- Optionally update weight names (if needed) --- */
    // In this example, weight names were already set correctly in init_model.
    
    /* --- Free intermediate matrices --- */
    free_matr(&X);
    free_matr(&X_T);
    free_matr(&XTX);
    free_matr(&XTX_inv);
    free_matr(&Y);
    free_matr(&XTy);
    free_matr(&w_mat);
    
    return model;
}

long double run_model(LR_Model *model, data_row input)
{
    long double result = 0.0;
    
    if (model->has_intercept) {
        result += model->weights[0];  // Intercept term.
        // Multiply each predictor weight with its corresponding input value.
        for (int i = 1; i < model->weight_count; i++) {
            result += model->weights[i] * input[i - 1];
        }
    } else {
        // No intercept: weights align directly with input columns.
        for (int i = 0; i < model->weight_count; i++) {
            result += model->weights[i] * input[i];
        }
    }
    return result;
}

void save_model(LR_Model *model, char *file_path)
{
    FILE *fp = fopen(file_path, "wb");
    if (fp == NULL) {
        fprintf(stderr, "Error opening file for writing.\n");
        goto error;
    }

    if (fwrite(&model->weight_count, sizeof(int), 1, fp) != 1 ||
        fwrite(&model->has_intercept, sizeof(bool), 1, fp) != 1) {
        fprintf(stderr, "Error writing model header.\n");
        goto error;
    }

    for (int i = 0; i < model->weight_count; i++) {
        if (fwrite(&model->weights[i], sizeof(long double), 1, fp) != 1) {
            fprintf(stderr, "Error writing weight value.\n");
            goto error;
        }

        int name_len = strlen(model->weight_names[i]) + 1;
        if (fwrite(&name_len, sizeof(int), 1, fp) != 1) {
            fprintf(stderr, "Error writing name length.\n");
            goto error;
        }

        if (fwrite(model->weight_names[i], sizeof(char), name_len, fp) != (size_t)name_len) {
            fprintf(stderr, "Error writing weight name.\n");
            goto error;
        }
    }

    fclose(fp);
    return;

error:
    if (fp != NULL) fclose(fp);
    exit(1);
}

LR_Model *load_model(char *file_path)
{
    FILE *fp = fopen(file_path, "rb");
    if (fp == NULL) {
        fprintf(stderr, "Error opening file for reading.\n");
        return NULL;
    }

    LR_Model *model = malloc(sizeof(LR_Model));
    if (!model) {
        fprintf(stderr, "Memory allocation error for LR_Model\n");
        goto error;
    }

    if (fread(&model->weight_count, sizeof(int), 1, fp) != 1 ||
        fread(&model->has_intercept, sizeof(bool), 1, fp) != 1) {
        fprintf(stderr, "Error reading model header.\n");
        goto error;
    }

    model->weights = malloc(sizeof(long double) * model->weight_count);
    model->weight_names = malloc(sizeof(char *) * model->weight_count);
    if (!model->weights || !model->weight_names) {
        fprintf(stderr, "Memory allocation error for weights or names\n");
        goto error;
    }

    for (int i = 0; i < model->weight_count; i++) {
        if (fread(&model->weights[i], sizeof(long double), 1, fp) != 1) {
            fprintf(stderr, "Error reading weight value.\n");
            goto error;
        }

        int name_len = 0;
        if (fread(&name_len, sizeof(int), 1, fp) != 1) {
            fprintf(stderr, "Error reading name length.\n");
            goto error;
        }

        model->weight_names[i] = malloc(name_len);
        if (!model->weight_names[i]) {
            fprintf(stderr, "Memory allocation error for weight name\n");
            goto error;
        }

        if (fread(model->weight_names[i], sizeof(char), name_len, fp) != (size_t)name_len) {
            fprintf(stderr, "Error reading weight name.\n");
            goto error;
        }
    }

    fclose(fp);
    return model;

error:
    if (fp) fclose(fp);
    if (model) {
        if (model->weight_names) {
            for (int i = 0; i < model->weight_count; i++) {
                free(model->weight_names[i]);
            }
            free(model->weight_names);
        }
        free(model->weights);
        free(model);
    }
    return NULL;
}
