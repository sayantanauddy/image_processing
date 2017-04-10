import numpy as np
import cv2
import scipy
import matplotlib as plt


def create_gaussian_kernel(kernel_size, sigma, normalize=False):

    # Calculate the center of the filter
    mid = (kernel_size // 2)
    print mid

    # Create a kernel_size*kernel_size Gaussian Kernel
    gaussian_kernel = np.zeros((kernel_size, kernel_size))
    for i in range(0, kernel_size):
        for j in range(0, kernel_size):
            gaussian_kernel[i][j] = (np.exp(-1.0*((i-mid)**2 + (j-mid)**2)/(2.0*sigma**2)))/(2*np.pi*sigma*sigma)

    if normalize:
        # Normalize the kernel
        for i in range(0, kernel_size):
            for j in range(0, kernel_size):
                gaussian_kernel[i][j] /= np.sum(gaussian_kernel)

    return gaussian_kernel



# Load an color image in grayscale
img = cv2.imread('../images/sunflower.jpg',0)

# Retrieve the shape of the image
img_shape = img.shape
rows = img_shape[0]
cols = img_shape[1]

kernel_size = 5
sigma = 1.0

kernel = create_gaussian_kernel(kernel_size, sigma, True)

print kernel

blurred_image = img.copy()

'''# i,j denotes the center of the kernel moving over the image
for i in range(0 + (kernel_size//2), rows - (kernel_size//2)):
    for j in range(0 + (kernel_size//2), rows - (kernel_size//2)):
        for x in range(-(kernel_size//2),kernel_size//2+1):
            for y in range(-(kernel_size//2),kernel_size//2+1):
                blurred_image[i+x][j+y] = img[i+x][j+y]*kernel[x+kernel_size//2][y+kernel_size//2]
'''

# Convolve the image with the kernel
dst = cv2.filter2D(img,-1,kernel)

cv2.imshow('image',dst)
cv2.waitKey(0)
cv2.destroyAllWindows()
