# Linear Regression Model in C

> A lightweight, self-contained linear regression implementation in pure C, featuring training, prediction, file persistence, and custom matrix/vector utilities — all built without relying on external libraries.

---

## 📚 Table of Contents

- [📁 Project Structure](#-project-structure)
- [⚙️ Features](#️-features)
- [📚 API Reference](#-api-reference)
  - [LR_Model](#lr_model-from-lr_modelh)
  - [Vector](#vector-api-from-vectorh)
  - [Matrix](#matrix-api-from-matrixh)
  - [🔧 Compilation](#-compilation)
- [🧠 How It Works](#-how-it-works)
- [🧱 Dependencies](#-dependencies)
- [🧼 Memory Management](#-memory-management)
- [🧪 Example Usage](#-example-usage-from-testerc)
- [📝 Future Improvements](#-future-improvements)
- [📄 License](#-license)

---

## 📁 Implemented Headers

```
.
├── LR_Model.h       # Core linear regression model interface
├── matrix.h         # Matrix operations, including transpose and inversion
├── vector.h         # Vector operations used throughout the model
```

---

## ⚙️ Features

- Train a linear regression model using one or more features  
- Support for intercepts  
- Save and load models from disk  
- Custom vector/matrix algebra implementation  
- Designed to be simple and easily extensible  

---

## 📚 API Reference

### LR_Model (from `LR_Model.h`)

| Function | Description |
|----------|-------------|
| `LR_Model *train_model(Feature *feats, Output *output, long feat_count, bool has_intercept)` | Train a linear regression model using features and output |
| `long double run_model(LR_Model *model, data_row input)` | Run the model on a new input to get a prediction |
| `void save_model(LR_Model *model, char *path)` | Serialize the model weights and metadata to a file |
| `LR_Model *load_model(char *path)` | Load a serialized model from a file |
| `void free_model(LR_Model *model)` | Free all memory used by the model |

---

### Vectors (from `vector.h`)

| Function | Description |
|----------|-------------|
| `Vector init_vec(long double *data, long size)` | Initialize a vector with provided data |
| `Vector empty_vec(long size)` | Create a vector of given size, initialized to zero |
| `void free_vec(Vector *v)` | Free memory allocated to a vector |
| `long double dot(Vector *v1, Vector *v2)` | Compute dot product between two vectors |

---

### Matrices (from `matrix.h`)

| Function | Description |
|----------|-------------|
| `Matrix init_matr(Vector *rows, long row_num)` | Initialize a matrix with an array of row vectors |
| `Matrix empty_matr(long row_num, long col_num)` | Create a zero-initialized matrix with given dimensions |
| `void free_matr(Matrix *m)` | Free memory allocated to the matrix |
| `long double *get_m_pos(Matrix *m, long row, long col)` | Get a pointer to a matrix element for direct modification |
| `long double get_m_val(Matrix *m, long row, long col)` | Retrieve a matrix value at a given position |
| `Vector *get_row(Matrix *m, long row_num)` | Get a pointer to a specific row vector |
| `Vector *get_col(Matrix *m, long col_num)` | Get a pointer to a specific column as a vector |
| `Matrix mul_matr(Matrix *m1, Matrix *m2)` | Matrix multiplication (m1 × m2) |
| `Matrix inv_matr(Matrix *m)` | Compute the inverse of a square matrix |
| `Matrix t_matrix(Matrix *m)` | Compute the transpose of a matrix |

---

### 🔧 Compilation

To compile and run the tester, ensure all `.c` files are included:

```bash
gcc tester.c LR_Model.c matrix.c vector.c -o tester
./tester
```

Make sure all headers and implementations are in the same directory or adjust your includes accordingly.

---

## 🧠 How It Works

- A **Feature** consists of a name and a vector of data points.  
- An **Output** is simply a Feature representing the target variable.

### `train_model()`
Builds a model from features and output using the **Normal Equation**:

```
w = (XᵀX)⁻¹ Xᵀy
```

### `run_model()`
Computes predictions using the trained weights:

```
ŷ = wᵀ ⋅ x
```

### `save_model()` and `load_model()`
Provide persistence by saving/loading weights and model metadata to/from disk.

---

## 🧱 Dependencies

This is a **pure C** project — no external libraries are required. It is self-contained with custom implementations for vectors and matrices.

---

## 🧼 Memory Management

- Call `free_model()` after using your model  
- Free any vectors you initialize with `empty_vec()`  
- Free any matrices if you expand the project further  

> ✅ **If used properly, this implementation leaks 0 bytes of memory — guaranteed no memory leaks.**

---

## 🧪 Example Usage (from [`tester.c`](./tester.c))

```c
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
```

---

## 📝 Future Improvements

- Implement regularization (e.g., Ridge regression)  
- Include gradient descent as an alternative to the Normal Equation  
- Add support for applying transformations to inputs and inverse transformations to outputs to model non-linear relationships.

---

## 📄 License

This project is open-source. Use it freely in your own projects!
