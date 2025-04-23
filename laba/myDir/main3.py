from PIL import Image

img = Image.open("img.png")

pixel_mass = img.load()

width, height = img.size
print(width, height)
for j in range(height):
    for i in range(width):
        r, g, b, a = pixel_mass[i, j]
        pixel_mass[i, j] = (255 - r, 255 - g, 255 - b, a)


img2 = img
img2.save("img2.png")

# from PIL import Image, ImageOps
#
#
# img = Image.open('img.png')
#
#
# img2 = ImageOps.invert(img)
# img2.save('img2.png')