import cv2
import sys
import numpy as np
import math

def crop_to_square(img_path, output_path="cropped_square.jpg"):
    # Read image
    img = cv2.imread(img_path)
    height, width = img.shape
    min_side = min(height, width)

    # Compute top-left corner for centered crop
    start_x = (width - min_side) // 2
    start_y = (height - min_side) // 2
    cropped = img[start_y:start_y + min_side, start_x:start_x + min_side]
    cv2.imwrite(output_path, cropped)
    cv2.imshow("Cropped Square", cropped)
    cv2.waitKey(0)
    cv2.destroyAllWindows()


def scale(image_path, output_path="scaled.jpg"):
    # Read image
    img = cv2.imread(image_path)
    # Resize to 20x20
    scaled = cv2.resize(img, (12, 12), interpolation=cv2.INTER_AREA)
    # Save and show
    cv2.imwrite(output_path, scaled)
    # Optional display
    cv2.imshow("Scaled 20x20", scaled)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

def convert_to_greyscale(image_path, output_path="greyscale_output.jpg"):
    # Read the image
    img = cv2.imread(image_path)

    # Convert to grayscale
    grey = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

    # Save the result
    cv2.imwrite(output_path, grey)
    # (Optional) Display the images
    cv2.imshow("Grayscale Image", grey)
    cv2.waitKey(0)
    cv2.destroyAllWindows()


def sampling(image_path, N, angle_deg):

    img = cv2.imread(image_path)

    height, width, toto = img.shape

    cx, cy = width//2, height//2


    # Convert angle to radians
    angle_rad = math.radians(angle_deg)

    # Generate coordinates for N pixels along the line
    pixel_values = []
    delta_len = (width//2)/N -1
    for i in range(1, N+1):
        x = int(cx + delta_len * i * math.cos(angle_rad))
        y = int(cy - delta_len * i * math.sin(angle_rad))  # minus because y increases downward
        pixel_values.append(int(img[y, x][0]))
    return pixel_values

def general_sampling(image_path, sample_value):
    list_pixel_values = []
    for precision in range(sample_value):
        print("indice ",precision, "angle ", precision * 360/sample_value)
        list_pixel_values.append(sampling(image_path, 20, precision * 360/sample_value))  
    return list_pixel_values



def place_grey_values(sample_general, image_size=(200, 200)):

    # Create blank grayscale image
    img = np.zeros(image_size, dtype=np.uint8)

    h, w = image_size
    cx, cy = w // 2, h // 2
    delta_len = (w//2)/len(sample_general[0]) -1
                           
    for angle_indice in range(len(sample_general)):
        # Draw each pixel along the line
        for line_indice in range(len(sample_general[0])):
            x = int(cx + delta_len * line_indice * math.cos(math.radians(angle_indice * 360/len(sample_general))))
            y = int(cy - delta_len * line_indice * math.sin(math.radians(angle_indice * 360/len(sample_general))))  # minus because y increases downward
            value = sample_general[angle_indice][line_indice]
            # Define bounds (clamped to image edges)
            y_min = max(0, y - 1)
            y_max = min(img.shape[0] - 1, y + 1)
            x_min = max(0, x - 1)
            x_max = min(img.shape[1] - 1, x + 1)
            # Assign value to 3x3 block
            img[y_min:y_max + 1, x_min:x_max + 1] = value

    cv2.imwrite("Redrawn.jpg", img)
    cv2.imshow("Redrawn", img)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    return img



if __name__ == "__main__":
   place_grey_values(general_sampling("greyscale_output.jpg", 1000))
   
