#!/usr/bin/python

# This work is licensed under the Creative Commons Attribution 3.0 United 
# States License. To view a copy of this license, visit 
# http://creativecommons.org/licenses/by/3.0/us/ or send a letter to Creative
# Commons, 171 Second Street, Suite 300, San Francisco, California, 94105, USA.

# from http://oranlooney.com/make-css-sprites-python-image-library/ 
# Orignial Author Oran Looney <olooney@gmail.com>

#mods by Josh Gourneau <josh@gourneau.com> to make one big horizontal sprite JPG with no spaces between images

# See: https://gist.githubusercontent.com/gourneau/939252/raw/a082642f1dc9917be8abfae8457d9e4089d9d449/python-pil-image-sprite.py


#### EXAMPLE USE
# The argument list is a list of files to be added to the spritesheet
# eg.
#  $ python python-pil-image-sprite.py output.png v images/*.png
#
# Will add all the png images in the images directory and save as output.png in vertical mode

# Edited BY Jacob Causon 2014-06-24
import os
from PIL import Image
import glob
import sys

#get your images using glob
####iconMap = glob.glob("images/*.png")
iconMap = sys.argv[3:]
#just take the even ones
iconMap = sorted(iconMap)
#iconMap = iconMap[::2]

print len(iconMap)

images = [Image.open(filename) for filename in iconMap]

print "%d images will be combined." % len(images)

#image_width, image_height = images[0].size
image_width = 0
image_height = 0

if sys.argv[2]=='h':
    for count, image in enumerate(images):
        w, h = image.size
        image_width = image_width + w
        image_height = max(image_height, h)
else:
    for count, image in enumerate(images):
        w, h = image.size
        image_width = max(image_width, w)
        image_height = image_height + h

master_width = image_width #(image_width * len(images) ) 
#seperate each image with lots of whitespace
master_height = image_height
print "the master image will by %d by %d" % (master_width, master_height)
print "creating image...",
master = Image.new(
    mode='RGBA',
    size=(master_width, master_height),
    color=(0,0,0,0))  # fully transparent

print "created."

location = 0
if sys.argv[2]=='h':
    for count, image in enumerate(images):
        # location = image_width*count
        print "adding %s at %d..." % (iconMap[count][1], location),
        master.paste(image,(location,0))
        print "added."
        w, h = image.size
        location = location + w
else:
    for count, image in enumerate(images):
        # location = image_width*count
        print "adding %s at %d..." % (iconMap[count][1], location),
        master.paste(image,(0,location))
        print "added."
        w, h = image.size
        location = location + h

print "done adding icons."

print "saving master.jpg...",
#master.save('master.jpg', transparency=0 )
master.save(sys.argv[1],"PNG")
print "saved!"

