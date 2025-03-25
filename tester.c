#include "LR_Model.h"

int main() {
    int n = 5;
    // Allocate and initialize vectors for features and output.
    Vector x = empty_vec(n), z = empty_vec(n), y = empty_vec(n);
    int primes[5] = {2, 3, 5, 7, 11};
    for (int i = 0; i < n; i++) {
        x.data[i] = i + 1;                   // x: 1, 2, 3, 4, 5
        z.data[i] = primes[i];               // z: 2, 3, 5, 7, 11
        y.data[i] = 1 + 2 * x.data[i] + 0.5 * z.data[i];
    }

    Feature feats[2] = { {"x", x}, {"z", z} };
    Output output = { "y", y };

    // Train the model (with intercept) on non-collinear data.
    LR_Model *model = train_model(feats, &output, 2, true);

    // Test input: new values x=6, z=13 (prediction: 1+2*6+0.5*13 = 19.5)
    long double input[] = { 6.0, 13.0 };

    save_model(model, "Test");
    printf("Prediction before save: %Lf\n", run_model(model, input));
    free_model(model);

    model = load_model("Test");
    printf("Prediction after load: %Lf\n", run_model(model, input));
    free_model(model);

    // Free allocated vectors
    free_vec(&x);
    free_vec(&z);
    free_vec(&y);

    return 0;
}
