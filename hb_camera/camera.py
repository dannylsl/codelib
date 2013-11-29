import pygame
import pygame.camera
import sys
from pygame.locals import *

pygame.init()
pygame.camera.init()

window = pygame.display.set_mode((640,480),0)
cam = pygame.camera.Camera("/dev/video0", (640,480))
cam.start()
image = cam.get_image()
pygame.image.save(image,'%s.png'%sys.argv[1])
cam.stop()

#while True:
#	image = cam.get_image()
#	pygame.image.save(image,'abc.jpg')
#	window.blit(image,(0,0))
#	pygame.display.flip()
#cam.stop()
