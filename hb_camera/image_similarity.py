import datetime
import sys

def image_similarity(filepath1, filepath2):
    from PIL import Image
    import math
    import operator
    import numpy
    image1 = Image.open(filepath1)
    image2 = Image.open(filepath2)
    if image1.size != image2.size or image1.getbands() != image2.getbands():
        return -1
    # create thumbnails - resize em
    image1 = get_thumbnail(image1)
    image2 = get_thumbnail(image2)
    s = 0
    for band_index, band in enumerate(image1.getbands()):
        m1 = numpy.array([p[band_index] for p in image1.getdata()]).reshape(*image1.size)
        m2 = numpy.array([p[band_index] for p in image2.getdata()]).reshape(*image2.size)
        s += numpy.sum(numpy.abs(m1-m2))
    return s

#sudo pip install PIL
def pil_image_similarity(filepath1, filepath2):
    from PIL import Image
    import math
    import operator

    image1 = Image.open(filepath1)
    image2 = Image.open(filepath2)

    image1 = get_thumbnail(img1)
    image2 = get_thumbnail(img2)

    h1 = image1.histogram()
    h2 = image2.histogram()

    rms = math.sqrt(reduce(operator.add,  list(map(lambda a,b: (a-b)**2, h1, h2)))/len(h1) )
    return rms

# sudo pip install numpy
def numpy_image_similarity(filepath1, filepath2):
    import Image
    from numpy import average, linalg, dot
    import sys
    images = [filepath1, filepath2]
    vectors = []
    norms = []
    for image in images:
        vector = []
        for pixel_tuple in Image.open(image).getdata():
            vector.append(average(pixel_tuple))
        vectors.append(vector)
        norms.append(linalg.norm(vector, 2))
    a, b = vectors
    a_norm, b_norm = norms
    res =dot(a / a_norm, b / b_norm)
    return res

print "============================================"
print "numpy_image_similarity"
print "============================================"
dt = datetime.datetime.now().strftime('%b-%d-%y %H:%M:%S')
print dt
img_s = numpy_image_similarity('%s'%sys.argv[1], '%s'%sys.argv[2])
print "image1 and image2 similarity = %f"%img_s
dt = datetime.datetime.now().strftime('%b-%d-%y %H:%M:%S')
print dt


#print "============================================"
#print "pil_image_similarity"
#print "============================================"
#dt = datetime.datetime.now().strftime('%b-%d-%y %H:%M:%S')
#print dt
#img_s = pil_image_similarity('black320_240.bmp', 'screeh320_240.bmp')
#print "image1 and image2 similarity = %f"%img_s
#dt = datetime.datetime.now().strftime('%b-%d-%y %H:%M:%S')
#print dt
