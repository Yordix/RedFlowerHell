from __future__ import print_function
# ------------------------------------------------------------------------------------------------
# Copyright (c) 2016 Microsoft Corporation
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
# associated documentation files (the "Software"), to deal in the Software without restriction,
# including without limitation the rights to use, copy, modify, merge, publish, distribute,
# sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all copies or
# substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
# NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
# DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
# ------------------------------------------------------------------------------------------------

# Tutorial sample #2: Run simple mission using raw XML

# Added modifications by Norbert Bátfai (nb4tf4i) batfai.norbert@inf.unideb.hu, mine.ly/nb4tf4i.1
# 2018.10.18, https://bhaxor.blog.hu/2018/10/18/malmo_minecraft
# 2020.02.02, NB4tf4i's Red Flowers, http://smartcity.inf.unideb.hu/~norbi/NB4tf4iRedFlowerHell


from builtins import range
import MalmoPython
import os
import sys
import time
import random
import json
import math

if sys.version_info[0] == 2:
    sys.stdout = os.fdopen(sys.stdout.fileno(), 'w', 0)  # flush print output immediately
else:
    import functools
    print = functools.partial(print, flush=True)

# Create default Malmo objects:

agent_host = MalmoPython.AgentHost()
try:
    agent_host.parse( sys.argv )
except RuntimeError as e:
    print('ERROR:',e)
    print(agent_host.getUsage())
    exit(1)
if agent_host.receivedArgument("help"):
    print(agent_host.getUsage())
    exit(0)

# -- set up the mission -- #
missionXML_file='nb4tf4i_d.xml'
with open(missionXML_file, 'r') as f:
    print("NB4tf4i's Red Flowers (Red Flower Hell) - DEAC-Hackers Battle Royale Arena\n")
    print("NB4tf4i vörös pipacsai (Vörös Pipacs Pokol) - DEAC-Hackers Battle Royale Arena\n\n")
    print("The aim of this first challenge, called nb4tf4i's red flowers, is to collect as many red flowers as possible before the lava flows down the hillside.\n")
    print("Ennek az első, az nb4tf4i vörös virágai nevű kihívásnak a célja összegyűjteni annyi piros virágot, amennyit csak lehet, mielőtt a láva lefolyik a hegyoldalon.\n")    
    print("Norbert Bátfai, batfai.norbert@inf.unideb.hu, https://arato.inf.unideb.hu/batfai.norbert/\n\n")    
    print("Loading mission from %s" % missionXML_file)
    mission_xml = f.read()
    my_mission = MalmoPython.MissionSpec(mission_xml, True)
    my_mission.drawBlock( 0, 0, 0, "lava")


class Hourglass:
    def __init__(self, charSet):
        self.charSet = charSet
        self.index = 0
    def cursor(self):
        self.index=(self.index+1)%len(self.charSet)
        return self.charSet[self.index]

hg = Hourglass('|/-\|')

class Steve:
    def __init__(self, agent_host):
        self.agent_host = agent_host
        self.x = 0
        self.y = 0
        self.z = 0        
        self.yaw = 0
        self.pitch = 0        
        
    def run(self):
        world_state = self.agent_host.getWorldState()
        # Loop until mission ends:
        #self.agent_host.sendCommand( "turn -1" )
        #time.sleep(0.05)
        self.agent_host.sendCommand( "turn 1" )
        time.sleep(0.05)
        self.agent_host.sendCommand( "turn 1" )
        time.sleep(0.05)
        i = 0
        for i in range(6):
            self.agent_host.sendCommand( "move 1" )
            self.agent_host.sendCommand( "strafe -1" )
            self.agent_host.sendCommand( "strafe -1" )
            #self.agent_host.sendCommand( "strafe -1" )
        for i in range(35):
            self.agent_host.sendCommand( "jumpmove 1" )
            time.sleep(0.01)
            self.agent_host.sendCommand( "move 1" )
            time.sleep(0.01)
            self.agent_host.sendCommand( "strafe -1" )
        self.agent_host.sendCommand( "move -1" )
        time.sleep(0.05)
        self.agent_host.sendCommand( "turn 1" )
        kor = 2
        i = 0
        #a = 0
        #m = 0
        fold = [10, 14, 16, 12]
        balvirag = [[2, 5, 8], [8, 7, 6] ,[6, 3, 0], [0, 1, 2]]
        jobbvirag = [[9, 12, 15], [9, 10, 11], [17, 14, 11], [15, 16, 17]]
        leftfind = False
        self.agent_host.sendCommand( "look 1" )
        self.agent_host.sendCommand( "look 1" )
        self.agent_host.sendCommand( "attack 1" )
        time.sleep(0.05)
        self.agent_host.sendCommand( "jumpmove 1" )
        time.sleep(0.05)

        while world_state.is_mission_running:
            #print("--- nb4tf4i arena -----------------------------------\n")
            if world_state.number_of_observations_since_last_state != 0:
                sensations = world_state.observations[-1].text
                #print("    sensations: ", sensations)                
                observations = json.loads(sensations)
                nbr3x3x3 = observations.get("nbr3x3", 0)
                #time.sleep(0.001)
                #print("    3x3x3 neighborhood of Steve: ", nbr3x3x3)
                
                if "Yaw" in observations:
                    self.yaw = int(observations["Yaw"])
                if "Pitch" in observations:
                    self.pitch = int(observations["Pitch"])
                if "XPos" in observations:
                    self.x = int(observations["XPos"])
                if "ZPos" in observations:
                    self.z = int(observations["ZPos"])        
                if "YPos" in observations:
                    self.y = int(observations["YPos"])  
                
                #print("    Steve's Coords: ", self.x, self.y, self.z)        
                #print("    Steve's Yaw: ", self.yaw)        
                #print("    Steve's Pitch: ", self.pitch)

                #if "LineOfSight" in observations:
                #    LineOfSight = observations["LineOfSight"]
                #    self.lookingat = LineOfSight["type"]

                for i in range(17):
                    if nbr3x3x3[i] == "red_flower":
                        if i == fold[kor]:
                            self.agent_host.sendCommand( "move -1" )
                            time.sleep(0.1)
                            self.agent_host.sendCommand( "attack 1" )
                            time.sleep(0.1)
                            self.agent_host.sendCommand( "jumpmove 1" )
                            time.sleep(0.1)
                            self.agent_host.sendCommand( "attack 1" )
                            time.sleep(0.1)
                            self.agent_host.sendCommand( "jumpuse" )
                            time.sleep(0.5)
                            self.agent_host.sendCommand( "strafe 1" )
                            time.sleep(0.1)
                            self.agent_host.sendCommand( "strafe 1" )
                            time.sleep(0.1)
                            self.agent_host.sendCommand( "move -1" )
                            time.sleep(0.1)
                            self.agent_host.sendCommand( "move -1" )
                            time.sleep(0.1)
                            if leftfind:
                                self.agent_host.sendCommand( "strafe 1" )
                                time.sleep(0.1)
                                self.agent_host.sendCommand( "strafe 1" )
                                time.sleep(0.1)
                                self.agent_host.sendCommand( "move -1" )
                                time.sleep(0.1)
                                self.agent_host.sendCommand( "move -1" )
                                time.sleep(0.1)
                                leftfind = False
                            break
                        if i == 13:
                            self.agent_host.sendCommand( "move -1" )
                            time.sleep(0.1)
                            self.agent_host.sendCommand( "attack 1" )
                            time.sleep(0.1)
                            self.agent_host.sendCommand( "jumpmove 1" )
                            time.sleep(0.1)
                            self.agent_host.sendCommand( "attack 1" )
                            time.sleep(0.1)
                            self.agent_host.sendCommand( "jumpuse" )
                            time.sleep(0.5)
                            self.agent_host.sendCommand( "strafe 1" )
                            time.sleep(0.1)
                            self.agent_host.sendCommand( "strafe 1" )
                            time.sleep(0.1)
                            self.agent_host.sendCommand( "move -1" )
                            time.sleep(0.1)
                            self.agent_host.sendCommand( "move -1" )
                            time.sleep(0.1)
                            if leftfind:
                                self.agent_host.sendCommand( "strafe 1" )
                                time.sleep(0.1)
                                self.agent_host.sendCommand( "strafe 1" )
                                time.sleep(0.1)
                                self.agent_host.sendCommand( "move -1" )
                                time.sleep(0.1)
                                self.agent_host.sendCommand( "move -1" )
                                time.sleep(0.1)
                                leftfind = False
                            break

                        if i < 9:
                            leftfind = True
                            self.agent_host.sendCommand( "strafe 1" )
                            time.sleep(0.1)
                            self.agent_host.sendCommand( "move -1" )
                            time.sleep(0.1)
                            self.agent_host.sendCommand( "move -1" )
                            time.sleep(0.1)

                            self.agent_host.sendCommand( "attack 1" )
                            time.sleep(0.1)
                            self.agent_host.sendCommand("jumpmove 1")
                            time.sleep(0.1)

                            self.agent_host.sendCommand( "attack 1" )
                            time.sleep(0.1)
                            self.agent_host.sendCommand("jumpmove 1")
                            time.sleep(0.1)

                            self.agent_host.sendCommand( "attack 1" )
                            time.sleep(0.1)
                            self.agent_host.sendCommand( "move -1" )
                            time.sleep(0.1)
                            self.agent_host.sendCommand( "move -1" )
                            time.sleep(0.1)
                            self.agent_host.sendCommand( "move 1" )
                            time.sleep(0.1)
                            self.agent_host.sendCommand( "move 1" )
                            time.sleep(0.1)
                            self.agent_host.sendCommand( "jumpuse" )
                            time.sleep(0.1)
                            self.agent_host.sendCommand( "jumpmove 1" )
                            time.sleep(0.1)
                            self.agent_host.sendCommand( "jumpstrafe -1" )
                            time.sleep(0.1)

                        else:
                            self.agent_host.sendCommand( "strafe -1" )
                            time.sleep(0.1)
                            self.agent_host.sendCommand( "move -1" )
                            time.sleep(0.1)
                            self.agent_host.sendCommand( "move -1" )
                            time.sleep(0.1)

                            self.agent_host.sendCommand( "attack 1" )
                            time.sleep(0.1)
                            self.agent_host.sendCommand( "jumpmove 1" )
                            time.sleep(0.1)

                            self.agent_host.sendCommand( "attack 1" )
                            time.sleep(0.1)
                            self.agent_host.sendCommand( "jumpmove 1" )
                            time.sleep(0.1)

                            self.agent_host.sendCommand( "attack 1" )
                            time.sleep(0.1)
                            self.agent_host.sendCommand( "move -1" )
                            time.sleep(0.1)
                            self.agent_host.sendCommand( "move -1" )
                            time.sleep(0.1)
                            self.agent_host.sendCommand( "move 1" )
                            time.sleep(0.1)
                            self.agent_host.sendCommand( "move 1" )
                            time.sleep(0.1)

                            self.agent_host.sendCommand( "jumpstrafe 1" )
                            time.sleep(0.1)
                            self.agent_host.sendCommand( "strafe 1" )
                            time.sleep(0.1)
                            self.agent_host.sendCommand( "strafe 1" )
                            time.sleep(0.1)
                            self.agent_host.sendCommand( "move -1" )
                            time.sleep(0.1)
                            self.agent_host.sendCommand( "move -1" )
                            time.sleep(0.1)
                            if leftfind:
                                self.agent_host.sendCommand( "strafe 1" )
                                time.sleep(0.1)
                                self.agent_host.sendCommand( "strafe 1" )
                                time.sleep(0.1)
                                self.agent_host.sendCommand( "move -1" )
                                time.sleep(0.1)
                                self.agent_host.sendCommand( "move -1" )
                                time.sleep(0.1)
                                leftfind = False
                            
                if nbr3x3x3[fold[kor]] == "dirt":
                    self.agent_host.sendCommand( "turn 1" )
                    time.sleep(0.05)
                    self.agent_host.sendCommand( "strafe 1" )
                    time.sleep(0.05)
                    kor += 1
                    if kor == 4:
                        kor -= 4

                self.agent_host.sendCommand( "move 1" )
                
            world_state = self.agent_host.getWorldState()

num_repeats = 1
for ii in range(num_repeats):

    my_mission_record = MalmoPython.MissionRecordSpec()

    # Attempt to start a mission:
    max_retries = 6
    for retry in range(max_retries):
        try:
            agent_host.startMission( my_mission, my_mission_record )
            break
        except RuntimeError as e:
            if retry == max_retries - 1:
                print("Error starting mission:", e)
                exit(1)
            else:
                print("Attempting to start the mission:")
                time.sleep(2)

    # Loop until mission starts:
    print("   Waiting for the mission to start ")
    world_state = agent_host.getWorldState()

    while not world_state.has_mission_begun:
        print("\r"+hg.cursor(), end="")
        time.sleep(0.15)
        world_state = agent_host.getWorldState()
        for error in world_state.errors:
            print("Error:",error.text)

    print("NB4tf4i Red Flower Hell running\n")
    steve = Steve(agent_host)
    steve.run()

print("Mission ended")
# Mission has ended.
