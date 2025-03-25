#include "LR_Model.h"

int main()
{
    int n = 5;
    
    // Create and initialize the x vector.
    Vector x_vec = empty_vec(n);
    for (int i = 0; i < n; i++) {
        x_vec.data[i] = (long double)i;
    }
    
    // Create and initialize the y vector (y = 4x + 3).
    Vector y_vec = empty_vec(n);
    for (int i = 0; i < n; i++) {
        y_vec.data[i] = 4 * x_vec.data[i] + 3;
    }
    
    // Setup feature using the x vector.
    Feature feats[1];
    feats[0].name = "x";
    feats[0].data = x_vec;
    
    // Setup output using the y vector.
    Output output;
    output.name = "y";
    output.data = y_vec;
    
    // Train the model with an intercept.
    LR_Model *model = train_model(feats, &output, 1, true);
    
    // Save the model to file "Test".
    save_model(model, "saved_model");

    // Define input as an array (for a model with an intercept, run_model will use input[0]).
    long double input[1] = {5.0};

    printf("Before: %Lf \n", run_model(model, input));

    // Free the model after use.
    free_model(model);

    // Reload the model from the file.
    model = load_model("Test");

    printf("After: %Lf \n", run_model(model, input));

    free_model(model);

    // Free the vectors allocated with empty_vec.
    free_vec(&x_vec);
    free_vec(&y_vec);

    return 0;
}
