#ifndef LR_MODEL_H
#define LR_MODEL_H

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "matrix.h"

typedef long double * data_row;

typedef struct {
    char * name;
    Vector data;
} Feature;

typedef Feature Output;

typedef struct {
    char ** weight_names;
    data_row weights;
    long weight_count;
    bool has_intercept;
} LR_Model;

LR_Model * init_model(Feature * feats, long feat_count, bool has_intercept);
void free_model(LR_Model *model);
LR_Model * train_model(Feature *feats, Output * output, long feat_count, bool has_intercept);
long double run_model(LR_Model * model, data_row input);
void save_model(LR_Model * model, char * file_path);
LR_Model * load_model(char * file_path);

#endif // LR_MODEL