import numpy as np
from sklearn.linear_model import LinearRegression

x = np.array([[0], [1], [2], [3], [4]])
y = 4 * x + 3

model = LinearRegression()
model.fit(x, y)

prediction = model.predict([[5]])
print("Prediction:", prediction[0])
