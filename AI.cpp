/*
*Author:-Pukar Giri
*Created On:-21Th December 2018 at 20:49
*File Name:-AI.cpp
*Project Name:-dlibprac
*Licence:- MIT
*Email:-crazzy.lx75@gmail.com
*/

#include "AI.h"


typedef struct
{
    action action1;
    float value;
} action_value;

bool operator<(const state state1, const state state2)
{
        return (
                state1.my_action  < state2.my_action &&
                state1.opp_action < state2.opp_action &&
                state1.distance         < state2.distance );
}

bool operator>(const state state1, const state state2)
{
        return (
                state1.my_action  > state2.my_action &&
                state1.opp_action > state2.opp_action &&
                        state1.distance         > state2.distance);
}

bool operator==(const state state1, const state state2)
{
    return (
        state1.my_action  == state2.my_action &&
        state1.opp_action == state2.opp_action &&
                state1.distance         == state2.distance);
}

bool operator<(const state_action_pair pair1, const state_action_pair pair2)
{
    return (pair1.state1 < pair2.state1 && pair1.action1 < pair2.action1);
}

bool operator>(const state_action_pair pair1, const state_action_pair pair2)
{
    return (pair1.state1 > pair2.state1 && pair1.action1 > pair2.action1);
}

bool operator==(const state_action_pair pair1, const state_action_pair pair2)
{
    return (pair1.state1 == pair2.state1 && pair1.action1 == pair2.action1);
}

bool comp_action_value(action_value pair1, action_value pair2)
{
    return pair1.value < pair2.value;
}

bool comp_key_value(key_value key_value1, key_value key_value2)
{
    return key_value1.pair < key_value1.pair;
}

bool comp_reward(float reward1, float reward2)
{
    return reward1 < reward2;
}

AI::AI(player & sel,player &opp, float epsilion, float alpha, float gamma) :
self{sel}, opponent{opp}
{
    load();
    this->epsilion = epsilion;
    this->alpha = alpha;
    this->gamma = gamma;
}

inline float AI::getq(state_action_pair pair)
{

    unsigned int x = 0;
    for (auto item : q)
    {
        if (item.pair == pair)
        {
            break;
        }
        x++;
    }
    if (x >= q.size())
        return 0.0;
    return q.at(x).value;
}

void AI::setq(state_action_pair pair, float value)
{
    unsigned int x = 0;
    for (auto item : q)
    {
        if (item.pair == pair)
        {
            break;
        }
        x++;
    }
    if (x >= q.size())
    {
        q.push_back({pair, value});
        std::sort(q.begin(), q.end(), comp_key_value);
        return;
    }
    q.at(x).value = value;
}

void AI::learnq(state state1, action action1, float reward, float value)
{
    state_action_pair state_action{state1, action1};
    float oldvalue = getq(state_action);
    //    if (gencount%1000==0)
    //    {
    //        printf("old value : %f\n", oldvalue);
    //    }
    if (oldvalue == 0)
    {
        //            printf("found new state \n");
        setq(state_action, reward);
        //            q.insert(std::make_pair(state_action,reward));
    }
    else
    {
        this->setq(state_action, oldvalue + this->alpha * (value - oldvalue));
    }
}

action AI::chooseaction(state state1)
{
    if ((random() % 100) < this->epsilion)
    {
        //printf("choosing randomly\n");
        switch (random() % 5)
        {
        case 0:
            return action::cwalkb;
        case 1:
            return action::cwalkf;
        case 2:
            return action::ckick;
        case 3:
            return action::cpunch;
        case 4:
            return action::cjump;
        default:
            return action::cidle;
        }
    }
    std::vector<action_value> qvals;
    qvals.push_back({action::cidle, this->getq({state1, action::cidle})});
    qvals.push_back({action::cjump, this->getq({state1, action::cjump})});
    qvals.push_back({action::cpunch, this->getq({state1, action::cpunch})});
    qvals.push_back({action::ckick, this->getq({state1, action::ckick})});
    qvals.push_back({action::cwalkb, this->getq({state1, action::cwalkb})});
    qvals.push_back({action::cwalkf, this->getq({state1, action::cwalkf})});
    action_value *x, *y;
    std::sort(qvals.begin(), qvals.end(), comp_action_value);
    std::vector<action_value> maxqs;
    //        if (gencount % 1010 == 0)
    //        {
    //            for (auto item :qvals)
    //            {
    //                printf("%f\t", item.value);
    //            }
    //            printf("\n");
    //        }
    for (auto qs : qvals)
    {
        if (qs.value == qvals[0].value)
        {
            maxqs.push_back(qs);
        }
    }
    unsigned long index = random() % maxqs.size();
    //        if (gencount % 1000 == 0)
    //        {
    //            printf("max q value: %f\nmin q value : %f \n", maxqs[index].value, qvals[qvals.size() - 1].value);
    //        }
    return maxqs[index].action1;
}

void AI::learn(state state1, action action1, float reward, state state2)
{
    std::vector<float> qvals;
    qvals.push_back(this->getq({state1, action::cidle}));
    qvals.push_back(this->getq({state1, action::cwalkb}));
    qvals.push_back(this->getq({state1, action::cwalkf}));
    qvals.push_back(this->getq({state1, action::cjump}));
    qvals.push_back(this->getq({state1, action::ckick}));
    qvals.push_back(this->getq({state1, action::cpunch}));
    std::sort(qvals.begin(), qvals.end(), comp_reward);
    float maxqnew = qvals[0];
    this->learnq(state1, action1, reward, reward + this->gamma * maxqnew);
}

inline state_action_pair AI::get_state_action_pair(state &state1, action &action1)
{
    return state_action_pair{state1, action1};
}

state AI::calc_state()
{
    int distance=abs(opponent.x-self.x);
    lastdistance=distance;
        return {self.current_action,opponent.current_action,distance};
}

float AI::calc_reward()
{
    float reward=0;
    if (self.noted) reward-=100;
    if (opponent.noted) reward+=200;
    else reward -=50;
    if (abs(opponent.x-self.x)>130)
    {
        if (lastdistance <= abs(self.x - opponent.x))reward += 50;
        else reward -= 50;
    }else reward +=20;
    if ((self.left&&self.x+70<opponent.x)||(!self.left&&self.x>opponent.x+70))reward+=50;
    else reward-=50;
//    cout<<"reward:"<<reward<<endl;
        return -reward;
}


void AI::drive()
{
    state newstate = calc_state();
    action action1 = chooseaction(newstate);

    if (gencount % 1000 == 0)
    {
        system("clear");
        printf("turncount:- %lld \nstate:- {%d,%d,%d}\n", this->gencount,newstate.distance,newstate.my_action,newstate.opp_action);;
        printf("idle count         : %lld\n", no_of_idle_choosen);
        printf("jump count           : %lld\n", no_of_jump_choosen);
        printf("left count         : %lld\n", no_of_left_choosen);
        printf("right count        : %lld\n", no_of_right_choosen);
        printf("kick choosen count : %lld\n", no_of_kick_choosen);
        printf("punch choosen count : %lld\n", no_of_punch_choosen);
        printf("q length : %ld s \n", q.size());
        printf("q size : %ld Bytes or %f KB\n", q.size() * sizeof(key_value), q.size() * sizeof(key_value) / 1024.0);
        printf("=======================================================\n\n");
        //            printf("actionchoosen : %d\n\n", action1);
    }
//    if (gencount%10000==0)dump();
    switch (action1)
    {
    case action::cidle:
        self.idle();
        no_of_idle_choosen++;
        break;
    case action::cwalkf:
        self.walkf();
        no_of_right_choosen++;
        break;
    case action::cwalkb:
        self.walkb();
        no_of_left_choosen++;
        break;
    case action::cjump:
        self.jump();
        no_of_jump_choosen++;
        break;
    case action::cpunch:
        self.punch();
        no_of_punch_choosen++;
        break;
    case action::ckick:
        self.kick();
        no_of_kick_choosen++;
        break;
    }
    if (gencount)
    {
        learn(laststate, lastaction, calc_reward(), newstate);
    }
    lastaction = action1;
    laststate = newstate;
    gencount++;
}



void AI::dump()
    {
        system("clear");
        cout<<"dumping the file"<<endl;
        ofstream outfile("mlvalue.clx");
        for( auto item : q)
        {
            outfile<<item.pair.state1.my_action<<endl;
            outfile<<item.pair.state1.opp_action<<endl;
            outfile<<item.pair.state1.distance<<endl;
            outfile<<item.pair.action1<<endl;
            outfile<<item.value<<endl;
            outfile<<endl;
        }
    }



void AI::load()
    {
        action action1;
        state_action_pair pair1;
        state state1;
        float value;
        key_value keyValue1;
        string line;
        ifstream infile("mlvalue.clx");
        while (getline(infile,line))
        {
            state1.my_action=action(stoi(line));
            getline(infile,line);
            state1.opp_action=action(stoi(line));
            getline(infile,line);
            state1.distance=stoi(line);
            pair1.state1=state1;
            getline(infile,line);
            action1=action (stoi(line));
            pair1.action1=action1;
            getline(infile,line);
            value=stof(line);
            keyValue1.value=value;
            keyValue1.pair=pair1;
            q.push_back(keyValue1);
            getline(infile,line);
        }
    }
