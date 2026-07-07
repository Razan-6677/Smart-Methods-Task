# Task 1 - Image Classification using Teachable Machine

## Task Description
1. Train an image recognition model using Teachable Machine by Google, using at least two classes, and evaluate the model.
2. Download the trained model in TensorFlow → Keras format.
3. Write a Python script that loads the model, accepts an input image, and predicts its class.
4. Submit the Python script, the exported model files, and a screenshot of the output.

## Model Training
The model was trained using [Teachable Machine](https://teachablemachine.withgoogle.com) with 3 classes (cat, dog, fish), then exported in TensorFlow → Keras format (`keras_model.h5` and `labels.txt`).

## Code
The script loads the exported Keras model, preprocesses an input image (resize to 224x224, normalize), and predicts its class with a confidence score.

See [predict.py](code/predict.py)

## Output
The model correctly classified the test image as cat with a confidence score of 0.9995.

![Prediction Output](images/output-screenshot.jpg)
