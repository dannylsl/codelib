#coding=utf-8 
import os
import sys
import pexpect

#os.system('openssl ca -in %s -out %s' % ( filename, "./usercert.pem"))
child = pexpect.spawn('openssl ca -in %s -out %s \n' % ( "new_userreq.pem", "./usercert.pem"))
child.logfile = sys.stdout
#child.expect('password for')
#child.send('fuck\n')
child.expect('Enter pass phrase for')
print child.after
child.send('123456\n')
#child.expect_exact('Sign the certificate? [y/n]:')
child.expect('y/n')
print child.before
child.send('y\n')
#child.expect_exact('1 out of 1 certificate requests certified, commit? [y/n]')
child.expect('y/n')
child.send('y\n')
child.expect('Data Base Updated')
print "DONE"
