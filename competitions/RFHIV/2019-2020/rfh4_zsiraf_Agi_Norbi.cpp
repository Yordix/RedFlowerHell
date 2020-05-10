// Malmo:
#include <AgentHost.h>
#include <ClientPool.h>
using namespace malmo;

// STL:
#include <cstdlib>
#include <exception>
#include <iostream>
#include <string.h>
#include <string>
using namespace std;

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#define delay boost::this_thread::sleep(boost::posix_time::milliseconds
#define ahsc agent_host.sendCommand
#define state world_state=agent_host.getWorldState()

AgentHost agent_host;
WorldState world_state;

void felmegy(); //DONE
void run(boost::property_tree::ptree); //DONE
void nbrindex(boost::property_tree::ptree); //DONE
bool keres(boost::property_tree::ptree); //????
bool falelottem(string[]); //DONE
void tamadas(); //DONE
bool is_there_flower(string[]); //kész
void turn_right(boost::property_tree::ptree); //DONE
void turn_left(boost::property_tree::ptree); //Almost_DONE
int calculateyaw(boost::property_tree::ptree); //DONE
void left_trim(boost::property_tree::ptree); //DONE
void right_trim(boost::property_tree::ptree); //DONE
bool virag_elottem(string[]); //TODO
void killing_zombies(boost::property_tree::ptree);
string what_see(boost::property_tree::ptree);
int mob_counter(boost::property_tree::ptree);
void lock_target(boost::property_tree::ptree);
int calc_pitch(boost::property_tree::ptree);
void vissza(boost::property_tree::ptree);

string nbr[27];
int y = 0;
int yaw = 0;
string lookingAt;
int mobs_killed = 0;
int lenez = 0;
int kor = 0;
int nf = 0;

int elottem = 0;
int ebalra = 0;
int ejobbra = 0;
int mogottem = 0;
int mbalra = 0;
int mjobbra = 0;
int jobbra = 0;
int balra = 0;
int virag = 0;
int seged = 1;
int hbsize = 0;

int n = 7;
int r = 0;

int main(int argc, const char **argv)
{
    try
    {
        agent_host.parseArgs(argc, argv);
    }
    catch( const exception& e )
    {
        cout << "ERROR: " << e.what() << endl;
        cout << agent_host.getUsage() << endl;
        return EXIT_SUCCESS;
    }
    if( agent_host.receivedArgument("help") )
    {
        cout << agent_host.getUsage() << endl;
        return EXIT_SUCCESS;
    }

    std::ifstream xmlf{"nb4tf4i_d4_Rudolf_hard.xml"};
    std::string xml{std::istreambuf_iterator<char>(xmlf), std::istreambuf_iterator<char>()};

    MissionSpec my_mission{xml, true};
   
    MissionRecordSpec my_mission_record("./saved_data.tgz");

    int attempts = 0;
    bool connected = false;
    do {
        try {
            agent_host.startMission(my_mission, my_mission_record);
            connected = true;
        }
        catch (exception & e) {
            cout << "Error starting mission: " << e.what() << endl;
            attempts += 1;
            if (attempts >= 3)
                return EXIT_FAILURE;    // Give up after three attempts.
            else
                boost::this_thread::sleep(boost::posix_time::milliseconds(1000));   // Wait a second and try again.
        }
    } while (!connected);

    cout << "Waiting for the mission to start" << flush;
    do {
        cout << "♥" << flush;
        boost::this_thread::sleep(boost::posix_time::milliseconds(100));
        world_state = agent_host.getWorldState();
    } while (!world_state.has_mission_begun);
    cout << endl;
    boost::property_tree::ptree pt;
    state;
    run(pt);
    calculateyaw(pt);
    delay(100));
    killing_zombies(pt);
    delay(100));
    vissza(pt);
    delay(100));
    felmegy();
    ahsc("pitch 0.2");
    do
    {
        state;
        cout << calc_pitch(pt) << endl;
    } while (calc_pitch(pt) < 75);
    ahsc("pitch 0");
    ahsc("move 1");
    delay(500));
    ahsc("move 0");
    delay(300));
    turn_left(pt);
    left_trim(pt);
    delay(200));
    ahsc("move 1");
    delay(3000));
    ahsc("jump 1");
    delay(100));
    ahsc("jump 0");
    delay(1000));
    ahsc("jump 1");
    delay(100));
    ahsc("jump 0");
    delay(260));
    ahsc("move 0");
    delay(100));
    turn_left(pt);
    left_trim(pt);
    delay(100));
    int b_f=0;
    do{
        state;
        run(pt);
        if(falelottem(nbr))
        {
            if (b_f == 1)
            {
                ahsc("jump 1");
                delay(100));
                ahsc("jump 0");
                delay(250));
                ahsc("move 0");
                turn_left(pt);
                left_trim(pt);
                state;
                nbrindex(pt);
                b_f++;
            }
            else
            {
                ahsc("move 0");
                delay(100));
                turn_left(pt);
                left_trim(pt);
                ahsc("strafe -1");
                delay(100));
                ahsc("strafe 0");
                state;
                nbrindex(pt);
                b_f++;   
            }
        }
        else
        {
            state;
            run(pt);
            nbrindex(pt);
            ahsc("move 1");
            delay(100));
            if (virag_elottem(nbr))
            {
                if (b_f == 1)
                {
                    ahsc("move -1");
                    delay(50));
                    ahsc("move 0");
                    tamadas();
                    delay(100));
                }
                else
                {
                    tamadas();
                    delay(100));
                }
            }
        }

    } while (b_f != 2);
    ahsc("move 1");
    while (falelottem(nbr) == false)
    {
        state;
        run(pt);
        if (virag_elottem(nbr))
        {
            ahsc("attack 1");
            delay(100));
            ahsc("attack 0");
            tamadas();
            delay(100));
        } 
        else
        {
            ahsc("move 1");
        }
    }
    ahsc("move -1");
    delay(500));
    ahsc("move 0");
    delay(100));
    ahsc("strafe -1");
    delay(1500));
    ahsc("strafe 0");
    delay(100));

    // main loop:
    do {
        state;
        run(pt);
        nbrindex(pt);
        cout << nbr[ebalra+9] << " " << nbr[elottem+9] << " " << nbr[ejobbra+9] << endl;
        if (falelottem(nbr) == true) 
        {
            kor++;
            ahsc("move 0");
            delay(200));
            turn_right(pt);
            right_trim(pt);
            if (kor == 5)
            {
                ahsc("strafe 1");
                delay(75));
                ahsc("strafe 0");
            }
            else
            {
                ahsc("strafe -1");
                delay(75));
                ahsc("strafe 0");
            }
            state;
            nbrindex(pt);
            cout << elottem << " " << mogottem << endl;
            cout << nbr[ebalra+9] << " " << nbr[elottem+9] << " " << nbr[ejobbra+9] << endl;
        }
        else
        {
            if (kor == 5 && nf == 0)
            {
                state;
                run(pt);
                nbrindex(pt);
                if (virag_elottem(nbr))
                {
                    state;
                    run(pt);
                    ahsc("move 0");
                    tamadas();
                    nf++;
                    delay(100));
                }
                else
                {
                    ahsc("move 1");
                }
            }
            else
            {
                state;
                run(pt);
                nbrindex(pt);
                ahsc("move 1");
                delay(100));
                if (keres(pt))
                {
                    if (nbr[ebalra] == "red_flower" || nbr[ebalra+9] == "red_flower")
                    {
                        state;
                        ahsc("attack 1");
                        delay(100));
                        ahsc("attack 0");
                        cout << "ebalra" << endl;
                        ahsc("move 0");
                        delay(100));
                        ahsc("strafe -1");
                        delay(200));
                        ahsc("strafe 0");
                        delay(100));
                        tamadas();
                        delay(100));
                    }
                    else if (nbr[ejobbra+9] == "red_flower" || nbr[ejobbra] == "red_flower")
                    {
                        state;
                        ahsc("attack 1");
                        delay(100));
                        ahsc("attack 0");
                        cout << "ejobbra" << endl;
                        ahsc("move 0");
                        delay(100));
                        ahsc("strafe 1");
                        delay(200));
                        ahsc("strafe 0");
                        delay(100));
                        tamadas();
                        delay(100));
                    }
                    else if (nbr[elottem+9] == "red_flower" || nbr[elottem] == "red_flower")
                    {
                        state;
                        ahsc("attack 1");
                        delay(100));
                        ahsc("attack 0");
                        cout << "elottem" << endl;
                        ahsc("move 0");
                        delay(100));
                        ahsc("move 1");
                        delay(100));
                        ahsc("move 0");
                        delay(100));
                        tamadas();
                        delay(100));
                    }
                }
            }
        }
        
        /*if (csapda(nbr) == true)
        {
            ahsc("move 1");
            delay(200));
            ahsc("jump 1");
            delay(100));
            ahsc("jump 0");
            ahsc("move 0");
            delay(500));
        }*/

        /*if (lava(nbr) == true)
        {
            ahsc("strafe -1");
            delay(100));
            ahsc("strafe -1");
            delay(100));
        }

        if (falelottem(nbr) == true)
        {
            ahsc("turn -1");
            delay(100));
            ahsc("strafe -1");
            delay(100));
        }
        
        ahsc("move 1");
        delay(15));*/

        state;

    } while (world_state.is_mission_running);

    cout << "Mission has stopped." << endl;

    return EXIT_SUCCESS;
}

//FGV-ek
void run(boost::property_tree::ptree pt)
{
    int i = -1;
    for (std::vector<boost::shared_ptr<TimestampedString>>::iterator it = 
    world_state.observations.begin();
    it!= world_state.observations.end(); ++it)
    {
        istringstream iss((*it)->text);
        boost::property_tree::read_json(iss, pt);
        y = stoi(pt.get<string>("YPos"));
        yaw = stoi(pt.get<string>("Yaw"));
        for (auto& e : pt.get_child("nbr3x3"))
        {
            ++i;
            nbr[i] = e.second.get<string>("");
        }
    }
    if (yaw < 0)
    {
        yaw = yaw+360;
    }
    else
    {
        yaw = yaw;
    }
    
    
    nbrindex(pt);
}

int calculateyaw(boost::property_tree::ptree pt)
{
    for (std::vector<boost::shared_ptr<TimestampedString>>::iterator it = 
    world_state.observations.begin();
    it!= world_state.observations.end(); ++it) 
    {
        istringstream iss((*it)->text);
        boost::property_tree::read_json(iss, pt);
        yaw = stoi(pt.get<string>("Yaw"));
    }
    if (yaw < 0)
    {
        return yaw+360;
    }
    else
    {
        return yaw;
    }
}

int calc_pitch(boost::property_tree::ptree pt)
{
    for (std::vector<boost::shared_ptr<TimestampedString>>::iterator it = 
    world_state.observations.begin();
    it!= world_state.observations.end(); ++it)
    {
        istringstream iss((*it)->text);
        boost::property_tree::read_json(iss, pt);
        lenez = stoi(pt.get<string>("Pitch"));
    }
    return lenez;
}

string what_see(boost::property_tree::ptree pt)
{
    for (std::vector<boost::shared_ptr<TimestampedString>>::iterator it = 
    world_state.observations.begin();
    it!= world_state.observations.end(); ++it)
    {
        istringstream iss((*it)->text);
        boost::property_tree::read_json(iss, pt);
        lookingAt = pt.get<std::string>("LineOfSight.type");
    }
    return lookingAt;
}

int mob_counter(boost::property_tree::ptree pt)
{
    for (std::vector<boost::shared_ptr<TimestampedString>>::iterator it = 
    world_state.observations.begin();
    it!= world_state.observations.end(); ++it)
    {
        istringstream iss((*it)->text);
        boost::property_tree::read_json(iss, pt);
        mobs_killed = pt.get<int>("MobsKilled");
    }
    return mobs_killed;
}

void right_trim(boost::property_tree::ptree pt)
{
    state;
    cout << "BELÉPTEM A RIGHT_TRIM FÜGGVÉNYBE!!!!!!!" << endl;
    if (calculateyaw(pt) <= 190 && calculateyaw(pt) >= 170)
    {
        if (calculateyaw(pt) > 180)
        {
            ahsc("turn -0.015");
            do
            {
                state;
                cout << calculateyaw(pt) << endl;
            } while (calculateyaw(pt) != 180);
            ahsc("turn 0");
            return;
        } 
        else if (calculateyaw(pt) < 180)
        {
            ahsc("turn 0.015");
            do
            {
                state;
                cout << calculateyaw(pt) << endl;
            } while (calculateyaw(pt) != 180);
            ahsc("turn 0");
            return;
        }
    } 
    else if (calculateyaw(pt) <= 280 && calculateyaw(pt) >= 260)
    {
        if (calculateyaw(pt) > 270)
        {
            ahsc("turn -0.015");
            do
            {
                state;
                cout << calculateyaw(pt) << endl;
            } while (calculateyaw(pt) != 270);
            ahsc("turn 0");
            return;
        } 
        else if (calculateyaw(pt) < 270)
        {
            ahsc("turn 0.015");
            do
            {
                state;
                cout << calculateyaw(pt) << endl;
            } while (calculateyaw(pt) != 270);
            ahsc("turn 0");
            return;
        }
    }
    else if ((calculateyaw(pt) >= 350 && calculateyaw(pt) <=359) || (calculateyaw(pt) <= 10 && calculateyaw(pt) >= 0))
    {
        if (calculateyaw(pt) >= 350 && calculateyaw(pt) < 360)
        {
            ahsc("turn 0.015");
            do
            {
                state;
                cout << calculateyaw(pt) << endl;
            } while (calculateyaw(pt) != 0);
            ahsc("turn 0");
            return;
        }
        else if (calculateyaw(pt) <= 10 && calculateyaw(pt) > 0) 
        {
            ahsc("turn -0.015");
            do
            {
                state;
                cout << calculateyaw(pt) << endl;
            } while (calculateyaw(pt) != 0);
            ahsc("turn 0");       
            return;     
        }
    }
    else if (calculateyaw(pt) >= 80 && calculateyaw(pt) <= 100)
    {
        if (calculateyaw(pt) > 90)
        {
            ahsc("turn -0.015");
            do
            {
                state;
                cout << calculateyaw(pt) << endl;
            } while (calculateyaw(pt) != 90);
            ahsc("turn 0");
            return;
        }
        else if (calculateyaw(pt) < 90)
        {
            ahsc("turn 0.015");
            do
            {
                state;
                cout << calculateyaw(pt) << endl;
            } while (calculateyaw(pt) != 90);
            ahsc("turn 0");
            return;
        }
    }
}

void left_trim(boost::property_tree::ptree pt)
{
    state;
    cout << "BELÉPTEM A LEFT_TRIM FÜGGVÉNYBE!!!!!!! EZ EGY DEBUG ÜZENET" << endl;
    if (calculateyaw(pt) <= 190 && calculateyaw(pt) >= 170)
    {
        if (calculateyaw(pt) > 180)
        {
            ahsc("turn -0.015");
            do
            {
                state;
                cout << calculateyaw(pt) << endl;
            } while (calculateyaw(pt) != 180);
            ahsc("turn 0");
            return;
        } 
        else if (calculateyaw(pt) < 180)
        {
            ahsc("turn 0.015");
            do
            {
                state;
                cout << calculateyaw(pt) << endl;
            } while (calculateyaw(pt) != 180);
            ahsc("turn 0");
            return;
        }
    } 
    else if (calculateyaw(pt) <= 280 && calculateyaw(pt) >= 260)
    {
        if (calculateyaw(pt) > 270)
        {
            ahsc("turn -0.015");
            do
            {
                state;
                cout << calculateyaw(pt) << endl;
            } while (calculateyaw(pt) != 270);
            ahsc("turn 0");
            return;
        } 
        else if (calculateyaw(pt) < 270)
        {
            ahsc("turn 0.015");
            do
            {
                state;
                cout << calculateyaw(pt) << endl;
            } while (calculateyaw(pt) != 270);
            ahsc("turn 0");
            return;
        }
    }
    else if ((calculateyaw(pt) >= 350 && calculateyaw(pt) < 360) || (calculateyaw(pt) <= 10 && calculateyaw(pt) >= 0))
    {
        if (calculateyaw(pt) >= 350 && calculateyaw(pt) < 360)
        {
            ahsc("turn 0.015");
            do
            {
                state;
                cout << calculateyaw(pt) << endl;
            } while (calculateyaw(pt) != 0);
            ahsc("turn 0");
            return;
        }
        else if (calculateyaw(pt) <= 10 && calculateyaw(pt) > 0) 
        {
            ahsc("turn -0.015");
            do
            {
                state;
                cout << calculateyaw(pt) << endl;
            } while (calculateyaw(pt) != 0);
            ahsc("turn 0");       
            return;     
        }
    }
    else if (calculateyaw(pt) >= 80 && calculateyaw(pt) <= 100)
    {
        if (calculateyaw(pt) > 90)
        {
            ahsc("turn -0.015");
            do
            {
                state;
                cout << calculateyaw(pt) << endl;
            } while (calculateyaw(pt) != 90);
            ahsc("turn 0");
            return;
        }
        else if (calculateyaw(pt) < 90)
        {
            ahsc("turn 0.015");
            do
            {
                state;
                cout << calculateyaw(pt) << endl;
            } while (calculateyaw(pt) != 90);
            ahsc("turn 0");
            return;
        }
    }
}

void turn_right(boost::property_tree::ptree pt)
{
    cout << "TURNING RIGHT" << endl;
    state;
    //if ((calculateyaw(pt)<=95) && (calculateyaw(pt)>=85))
    if (calculateyaw(pt) == 90)
    {
        ahsc("turn 0.2");
        do
        {
            state;
            cout << calculateyaw(pt) << endl;
        } while (calculateyaw(pt) < 170);
        delay(10));
        ahsc("turn 0");
        state;
        return;
    }
    //else if ((calculateyaw(pt)>=185) && (calculateyaw(pt)<=175))
    else if (calculateyaw(pt) == 180)
    {
        ahsc("turn 0.2");
        do
        {
            state;
            cout << calculateyaw(pt) << endl;
        } while (calculateyaw(pt) < 260);
        delay(10));
        ahsc("turn 0");
        state;
        return;
    }
    //else if ((calculateyaw(pt)<=275) && (calculateyaw(pt)>=265))
    else if (calculateyaw(pt) == 270)
    {
        ahsc("turn 0.2");
        do
        {
            state;
            cout << calculateyaw(pt) << endl;
        } while (calculateyaw(pt) < 350);
        delay(10));
        ahsc("turn 0");
        state;
        return;
    }
    //else if (((calculateyaw(pt)>=355) && (calculateyaw(pt)<360)) || ((calculateyaw(pt)>=0) && (calculateyaw(pt)<=5)))
    else if (calculateyaw(pt) == 0)
    {
        ahsc("turn 0.2");
        do
        {
            state;
            cout << calculateyaw(pt) << endl;
        } while (calculateyaw(pt) < 80);
        delay(10));
        ahsc("turn 0");
        state;
        return;
    }
}

void turn_left(boost::property_tree::ptree pt)
{
    cout << "TURNING LEFT" << endl;
    state;
    if (calculateyaw(pt) == 90)
    {
        ahsc("turn -0.2");
        delay(1000));
        do
        {
            state;
            cout << calculateyaw(pt) << endl;
        } while (calculateyaw(pt) > 10);
        delay(10));
        ahsc("turn 0");
        state;
        return;
    }
    else if (calculateyaw(pt) == 180)
    {
        ahsc("turn -0.2");
        delay(1000));
        do
        {
            state;
            cout << calculateyaw(pt) << endl;
        } while (calculateyaw(pt) > 100);
        delay(10));
        ahsc("turn 0");
        state;
        return;
    }
    else if (calculateyaw(pt) == 270)
    {
        ahsc("turn -0.2");
        delay(1000));
        do
        {
            state;
            cout << calculateyaw(pt) << endl;
        } while (calculateyaw(pt) > 190);
        delay(10));
        ahsc("turn 0");
        state;
        return;
    }
    else if (calculateyaw(pt) == 0)
    {
        ahsc("turn -0.2");
        delay(1000));
        do
        {
            state;
            cout << calculateyaw(pt) << endl;
        } while (calculateyaw(pt) > 280);
        delay(10));
        ahsc("turn 0");
        state;
        return;
    }
}

void nbrindex(boost::property_tree::ptree pt)
{
    if (calculateyaw(pt) <= 135 && calculateyaw(pt) >= 45) //90 fok
    {
        ebalra = 6;
        elottem = 3;
        ejobbra = 0;
        balra = 7;
        jobbra = 1;
        mbalra = 8;
        mogottem = 5;
        mjobbra = 2;
    }
    else if (calculateyaw(pt) <= 225 && calculateyaw(pt) >= 135) //180 fok
    {
        ebalra = 0;
        elottem = 1;
        ejobbra = 2;
        balra = 3;
        jobbra = 5;
        mbalra = 6;
        mogottem = 7;
        mjobbra = 8;
    }
    else if (calculateyaw(pt) <= 315 && calculateyaw(pt) >= 225) //270 fok
    {
        ebalra = 2;
        elottem = 5;
        ejobbra = 8;
        balra = 1;
        jobbra = 7;
        mbalra = 0;
        mogottem = 3;
        mjobbra = 6;
    }
    else if (calculateyaw(pt) >= 315 && calculateyaw(pt) < 360) //360 fok
    {
        ebalra = 8;
        elottem = 7;
        ejobbra = 6;
        balra = 5;
        jobbra = 3;
        mbalra = 2;
        mogottem = 1;
        mjobbra = 0;
    }
    else if (calculateyaw(pt) <= 45 && calculateyaw(pt) >= 0) //0 fok
    {
        ebalra = 8;
        elottem = 7;
        ejobbra = 6;
        balra = 5;
        jobbra = 3;
        mbalra = 2;
        mogottem = 1;
        mjobbra = 0;
    }
    
}

void felmegy()
{
    state;
    boost::property_tree::ptree pt;
    run(pt);
    ahsc("move 1");
    delay(1500));
    ahsc("move 0");
    for(y=0; y < n+1; run(pt))
    {
        state;
        run(pt);
        ahsc("move 1");
        delay(500));
        ahsc("jump 1");
        delay(100));
        ahsc("jump 0");
        ahsc("move 0");
        delay(100));

    }
    ahsc("move 1");
    delay(100));
    ahsc("move 0");
}

bool falelottem(string nbr[])
{
    if ((nbr[ebalra+9]=="bedrock") && (nbr[elottem+9]=="bedrock") && (nbr[ejobbra+9]=="bedrock"))
    {
        return true;
    } else
    {
        return false;
    }
    
}

bool virag_elottem(string nbr[])
{
    if (nbr[elottem+9] == "red_flower")
    {
        return true;
    }
    else
    {
        return false;
    }
}

void tamadas()
{
    ahsc("attack 1");
    delay(100));
    ahsc("attack 0");
    ahsc("move -1");
    delay(225));
    ahsc("move 0");
    delay(100));
    ahsc("attack 1");
    delay(100));
    ahsc("attack 0");
    delay(100));
    return;
}

void killing_zombies(boost::property_tree::ptree pt)
{
    ahsc("move 1");
    delay(250));
    ahsc("move 0");
    ahsc("pitch 1");
    delay(200));
    ahsc("pitch 0");
    delay(100));
    ahsc("Hotbar.3 1");
    delay(50));
    ahsc("Hotbar.3 0");
    delay(50));
    ahsc("turn 0.6");
    do
    {
        state;
        mob_counter(pt);
        mobs_killed = mob_counter(pt);
        if (what_see(pt) == "Zombie")
        {
            state;
            calculateyaw(pt);
            mob_counter(pt);
            ahsc("turn 0");
            ahsc("attack 1");
            delay(100));
            ahsc("attack 0");
            delay(100));
            lock_target(pt);
            delay(100));
        }
        else
        {
            state;
        }
    } while (mobs_killed != 2);
    cout << "MEGÖLTEM A 2 ZOMBIT!!!!" << endl;
    delay(100));
    state;
}

void lock_target(boost::property_tree::ptree pt)
{
    cout << "TARGET LOCKED" << endl;
    state;
    mob_counter(pt);
    calculateyaw(pt);
    mobs_killed = mob_counter(pt);
    int cur_kil = mob_counter(pt)+1;
    int left_yaw = calculateyaw(pt)+35;
    cout << left_yaw << endl;
    int right_yaw = calculateyaw(pt)-35;
    cout << right_yaw << endl;
    if (left_yaw >= 360)
    {
        left_yaw = left_yaw-360;
    }
    cout << left_yaw << endl;
    if (right_yaw < 0)
    {
        right_yaw = right_yaw+360;
    }
    cout << right_yaw << endl;
    do
    {
        if (calculateyaw(pt) < left_yaw)
        {
            ahsc("turn 0.4");
            do
            {
                state;
                if (what_see(pt) == "Zombie")
                {
                    state;
                    ahsc("attack 1");
                    delay(100));
                    ahsc("attack 0");
                }
            } while (calculateyaw(pt) < left_yaw);
            ahsc("turn 0");
        }
        else if (calculateyaw(pt) > right_yaw)
        {
            ahsc("turn -0.4");
            do
            {
                state;
                if (what_see(pt) == "Zombie")
                {
                    state;
                    ahsc("attack 1");
                    delay(100));
                    ahsc("attack 0");
                }
            } while (calculateyaw(pt) > right_yaw);
            ahsc("turn 0");
        }
        else if (calculateyaw(pt) < right_yaw && calculateyaw(pt) > left_yaw)
        {
            ahsc("turn 0.4");
            do
            {
                state;
                if (what_see(pt) == "Zombie")
                {
                    state;
                    ahsc("attack 1");
                    delay(100));
                    ahsc("attack 0");
                }
            } while (calculateyaw(pt) > left_yaw);
            ahsc("turn 0");
            delay(100));
            ahsc("turn 0.4");
            do
            {
                state;
                if (what_see(pt) == "Zombie")
                {
                    state;
                    ahsc("attack 1");
                    delay(100));
                    ahsc("attack 0");
                }
            } while (calculateyaw(pt) < left_yaw);
            ahsc("turn 0");
        }
        else if (calculateyaw(pt) > left_yaw && calculateyaw(pt) < right_yaw)
        {
            ahsc("turn -0.4");
            do
            {
                state;
                if (what_see(pt) == "Zombie")
                {
                    state;
                    ahsc("attack 1");
                    delay(100));
                    ahsc("attack 0");
                }
            } while (calculateyaw(pt) < right_yaw);
            ahsc("turn 0");
            delay(100));
            ahsc("turn -0.4");
            do
            {
                state;
                if (what_see(pt) == "Zombie")
                {
                    state;
                    ahsc("attack 1");
                    delay(100));
                    ahsc("attack 0");
                }
            } while (calculateyaw(pt) > right_yaw);
            ahsc("turn 0");
        }
        mobs_killed = mob_counter(pt);
    } while (mobs_killed != cur_kil);
    ahsc("pitch -1");
    delay(100));
    ahsc("pitch 0");
    ahsc("turn 0.6");
    cout << "MEGÖLTEM 1 ZOMBIT" << endl;
}

bool keres(boost::property_tree::ptree pt)
{
    state;
    run(pt);
    nbrindex(pt);
    bool fl = (nbr[ebalra] == "red_flower");
    bool fl_p = (nbr[ebalra+9] == "red_flower");
    bool fr = (nbr[ejobbra] == "red_flower");
    bool fr_p = (nbr[ejobbra+9] == "red_flower");
    bool front = (nbr[elottem] == "red_flower");
    bool front_p = (nbr[elottem+9] == "red_flower");
    if (fl || fl_p)
    {
        return true;
    }
    else if (fr || fr_p)
    {
        return true;
    }
    else if (front || front_p)
    {
        return true;
    }
    else
    {
        return false;
    }
    return false;   
}

void vissza(boost::property_tree::ptree pt)
{
    state;
    calculateyaw(pt);
    ahsc("turn 0.4");
    do
    {
        state;
    } while (calculateyaw(pt) < 80 || calculateyaw(pt) > 90);
    ahsc("turn 0");
    ahsc("turn 0.015");
    do
    {
        state;
    } while (calculateyaw(pt) != 90);
    ahsc("turn 0");
}