# Linear Regression Model in C

This project provides a lightweight, modular implementation of a Linear Regression (LR) model in C. It supports model training, inference, and persistence (saving/loading to/from files), and is built on custom Vector and Matrix abstractions.

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

### `LR_Model *train_model(...)`
Train a linear regression model using features and output.

### `long double run_model(LR_Model *model, data_row input)`
Run the model on a new input to get the prediction.

### `void save_model(LR_Model *model, char *path)`
Serialize the model weights and intercept info to a file.

### `LR_Model *load_model(char *path)`
Load a model back into memory from the file.

### `void free_model(LR_Model *model)`
Release all memory allocated to the model.

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

- Add support for multiple features  
- Implement regularization (e.g., Ridge regression)  
- Include gradient descent as an alternative to the Normal Equation  
- Build a full test suite  

---

## 📄 License

This project is open-source. Use it freely in your own projects!

---

Let me know if you’d like a Makefile, unit tests, or to split header/source files too!
# Linear Regression Model in C

This project provides a lightweight, modular implementation of a Linear Regression (LR) model in C. It supports model training, inference, and persistence (saving/loading to/from files), and is built on custom Vector and Matrix abstractions.

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

### `LR_Model *train_model(...)`
Train a linear regression model using features and output.

### `long double run_model(LR_Model *model, data_row input)`
Run the model on a new input to get the prediction.

### `void save_model(LR_Model *model, char *path)`
Serialize the model weights and intercept info to a file.

### `LR_Model *load_model(char *path)`
Load a model back into memory from the file.

### `void free_model(LR_Model *model)`
Release all memory allocated to the model.

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

- Add support for multiple features  
- Implement regularization (e.g., Ridge regression)  
- Include gradient descent as an alternative to the Normal Equation  
- Build a full test suite  

---

## 📄 License

This project is open-source. Use it freely in your own projects!

---