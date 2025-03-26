import numpy as np
import joblib
from sklearn.linear_model import LinearRegression

# Input features
x = np.array([1, 2, 3, 4, 5])
z = np.array([2, 3, 5, 7, 11])

# Stack x and z as columns to form the input matrix
X = np.column_stack((x, z))

# Output: y = 1 + 2*x + 0.5*z
y = 1 + 2 * x + 0.5 * z

# Train the linear regression model with intercept
model = LinearRegression()
model.fit(X, y)

# New input: x = 6, z = 13
test_input = np.array([[6, 13]])
prediction_before = model.predict(test_input)[0]
print("Prediction before save:", prediction_before)

# Save the model to disk
joblib.dump(model, "model.joblib")

# Load the model back
loaded_model = joblib.load("model.joblib")

# Predict using the loaded model
prediction_after = loaded_model.predict(test_input)[0]
print("Prediction after load:", prediction_after)