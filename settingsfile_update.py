#!/usr/bin/env python
import os
import tarfile
import json
import urllib2
import urllib
import sys
baseUrl = "https://rr123.applanga.com/"
#baseUrl = "http://localhost:3000/"

def fix_unicode(data):
    if isinstance(data, unicode):
        return data.encode('utf-8')
    elif isinstance(data, dict):
        data = dict((fix_unicode(k), fix_unicode(data[k])) for k in data)
    elif isinstance(data, list):
        for i in xrange(0, len(data)):
            data[i] = fix_unicode(data[i])
    return data

if len(sys.argv) < 2 :
	print "Applanga Automatic Settings File Update: Specify project directory."
	sys.exit(1)


projectPath = sys.argv[1];
#this file has to be in your project root dir
print "-> searching for applanga settingfiles in " + projectPath
for root, dirs, files in os.walk(projectPath):
	for file in files:
		if file.endswith(".applanga"):
			try:
				path = os.path.join(root,file)
				print "--> found: '%s' in '%s'" % (file, path[len(os.getcwd())+1: len(path)])
				tar = tarfile.open(path)
				alData = json.load(tar.extractfile(tar.getmember("app.applanga")))
				appId = alData["_id"];
				apiSecret = alData["apiSecret"]
				lastVersion = alData["__v"]
				if not "groupIds" in  alData.keys():
					print "Error: Your settingsfile is to old please update manually once before using the auto update script."
					continue
				groupIds = alData["groupIds"]
			except (Exception):
				print "Settingsfile parsing error"
			else:	
				try:
					url = "%sv1/projects/%s/updateSettings?apiSecret=%s&lastVersion=%s&%s" % (baseUrl, appId, apiSecret, lastVersion, urllib.urlencode({'groupIds[]': fix_unicode(groupIds)}, True))
					responseJson = json.loads(urllib2.urlopen(url).read())
					if responseJson["update"] == True:
						os.remove(path)
						if not os.path.isfile(path):
							newSettingsFile = urllib.URLopener()
							newSettingsFile.retrieve(responseJson["settings"], path)
							print "---> Settingsfile updated!"
					else:
						print "---> Settingsfile up-to-date"	
					tar.close()
				except (Exception):
					print "Settingsfile update error:", sys.exc_info()
