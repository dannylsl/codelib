import pygame
import pygame.camera
from pygame.locals import *

pygame.init()
pygame.camera.init()

window = pygame.display.set_mode((320,240),0)
cam = pygame.camera.Camera("/dev/video0", (320,240))
cam.start()
##image = cam.get_image()
##pygame.image.save(image,'abc.jpg')
##cam.stop()
while True:
	image = cam.get_image()
	pygame.image.save(image,'abc.bmp')
	window.blit(image,(0,0))
	pygame.display.flip()
cam.stop()
