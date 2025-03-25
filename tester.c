#include "LR_Model.h"

int main() {

    int n = 5; // Number of datapoints

    // Allocate and initialize vectors for features and output.
    // `empty_vec(int n)` returns a zero-initialized vector of length n.
    Vector x = empty_vec(n), z = empty_vec(n), y = empty_vec(n);
    
    int primes[5] = {2, 3, 5, 7, 11};
    
    for (int i = 0; i < n; i++) {
        x.data[i] = i + 1;                   // x: 1, 2, 3, 4, 5
        z.data[i] = primes[i];               // z: 2, 3, 5, 7, 11
        y.data[i] = 1 + 2 * x.data[i] + 0.5 * z.data[i];  // Linear target function
    }
    
    // Create feature array using vectors x and z
    Feature feats[2] = {
        { "x", x },
        { "z", z }
    };
    
    // Output vector for training
    Output output = { "y", y };
    
    // Train the linear regression model with intercept using the features and output.
    // `train_model` fits the model and returns a pointer to it.
    LR_Model *model = train_model(feats, &output, 2, true);
    
    // Define new test input: x = 6, z = 13
    // Expected prediction: 1 + 2*6 + 0.5*13 = 19.5
    long double input[] = { 6.0, 13.0 };
    
    // Save the trained model to a file named "Test"
    // `save_model` writes the model parameters to disk
    save_model(model, "Test");
    
    // Make a prediction using the trained model before saving
    // `run_model` returns the predicted output for the given input features
    printf("Prediction before save: %Lf\n", run_model(model, input));
    
    // Free the memory allocated for the model
    // `free_model` releases all resources associated with the model
    free_model(model);
    
    // Reload the model from the saved file "Test"
    // `load_model` reads the model parameters from disk and returns a pointer
    model = load_model("Test");
    
    // Make a prediction using the reloaded model
    printf("Prediction after load: %Lf\n", run_model(model, input));
    
    // Free the model again after use
    free_model(model);
    
    // Free the memory allocated for all vectors
    // `free_vec` releases internal data held by the vector
    free_vec(&x);
    free_vec(&z);
    free_vec(&y);    

    return 0;
}
