# Linear Regression Model in C

> ⚠️ **Disclaimer**  
> Although this is a video coding–free project, **AI has been used to generate the beautiful documentation below**, which helps both the publisher and the user without preventing the publisher from learning the presented content!  
> Users are encouraged to do the same when using or extending this implementation — let documentation enhance, not replace, your learning process.

---

## 📁 Project Structure

```
.
├── LR_Model.h       # Core linear regression model interface
├── tester.c         # Demo/tester for training and saving/loading a model
├── vector.h         # Vector operations used throughout the model
├── matrix.h         # Matrix operations, including transpose and inversion
```

---

## ⚙️ Features

- Train a linear regression model using one or more features  
- Support for intercepts  
- Save and load models from disk  
- Custom vector/matrix algebra implementation  
- Designed to be simple and easily extensible  

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

## 🧪 Example Usage (from `tester.c`)

```c
int n = 5;

// Create input vector x = [0, 1, 2, 3, 4]
Vector x_vec = empty_vec(n);
for (int i = 0; i < n; i++) x_vec.data[i] = i;

// Output y = 4x + 3
Vector y_vec = empty_vec(n);
for (int i = 0; i < n; i++) y_vec.data[i] = 4 * i + 3;

// Feature and output setup
Feature feats[1] = { { "x", x_vec } };
Output output = { "y", y_vec };

// Train model with intercept
LR_Model *model = train_model(feats, output, 1, true);

// Save, load, and run
save_model(model, "Test");
printf("Prediction before save: %Lf\n", run_model(model, (long double[]){5.0}));
free_model(model);
model = load_model("Test");
printf("Prediction after load: %Lf\n", run_model(model, (long double[]){5.0}));
```

---

## 🔧 Compilation

To compile and run the tester:

```bash
gcc tester.c -o tester
./tester
```

Make sure all headers and implementations are in the same directory or adjust your includes accordingly.

---

## 📚 API Reference

### LR_Model (from `LR_Model.h`)

| Function | Description |
|----------|-------------|
| `LR_Model *train_model(Feature *feats, Output output, long feat_count, bool has_intercept)` | Train a linear regression model using features and output |
| `long double run_model(LR_Model *model, data_row input)` | Run the model on a new input to get a prediction |
| `void save_model(LR_Model *model, char *path)` | Serialize the model weights and metadata to a file |
| `LR_Model *load_model(char *path)` | Load a serialized model from a file |
| `void free_model(LR_Model *model)` | Free all memory used by the model |

---

### Vector API (from `vector.h`)

| Function | Description |
|----------|-------------|
| `Vector init_vec(long double *data, long size)` | Initialize a vector with provided data |
| `Vector empty_vec(long size)` | Create a vector of given size, initialized to zero |
| `void free_vec(Vector *v)` | Free memory allocated to a vector |
| `long double dot(Vector *v1, Vector *v2)` | Compute dot product between two vectors |

---

### Matrix API (from `matrix.h`)

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

## 🧱 Dependencies

This is a **pure C** project — no external libraries are required. It is self-contained with custom implementations for vectors and matrices.

---

## 🧼 Memory Management

Don’t forget to:

- Call `free_model()` after using your model
- Free any vectors you initialize with `empty_vec()`
- Free any matrices if you expand this further

---

## 📝 Future Improvements

- Implement regularization (e.g., Ridge regression)  
- Include gradient descent as an alternative to the Normal Equation  
- Build a full test suite  

---

## 📄 License

This project is open-source. Use it freely in your own projects!
