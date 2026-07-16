# Task 2 - Face Recognition using OpenCV

## Task Description
Make a project using OpenCV for one of the computer vision tasks: **Face Recognition**. 
The objective is to build a Python script capable of detecting specific facial features (Face, Eyes, and Smile) from an input image and drawing bounding boxes around them.

## Implementation Details
The model was implemented using OpenCV's pre-trained Haar Cascade Classifiers:
- [`haarcascade_frontalface_default.xml`](https://github.com/opencv/opencv/blob/4.x/data/haarcascades/haarcascade_frontalface_default.xml) (Face detection)
- [`haarcascade_eye.xml`](https://github.com/opencv/opencv/blob/4.x/data/haarcascades/haarcascade_eye.xml) (Eye detection)
- [`haarcascade_smile.xml`](https://github.com/opencv/opencv/blob/4.x/data/haarcascades/haarcascade_smile.xml) (Smile detection)

## Code
The script loads the input image, converts it to grayscale for processing, and applies the `detectMultiScale` method to locate the features. It then uses `cv2.rectangle` to draw labeled bounding boxes around the detected areas.

See [AiTask.py](code/AiTask.py)

## Output
The script successfully recognized the facial features, drawing a red box around the face, green boxes around the eyes, and a blue box around the smile.

![Face Recognition Output](images/task%202.png)
