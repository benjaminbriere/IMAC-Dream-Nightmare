#include "game/Torchlight.hpp"

namespace game {

    Torchlight::Torchlight()
    {
        _lifeTime = 100;
        _nbBatteries = 1; 
        _frames = 0;         
    }

    Torchlight::~Torchlight()
    {

    }

    int Torchlight::getNbBatteries(){
        return _nbBatteries; 
    }		
    
    void Torchlight::setNbBatteries(int v){
        _nbBatteries += v;
    }

    int Torchlight::getLifeTime(){
        return _lifeTime;
    }
                
    void Torchlight::setLifeTime(int v){
        _lifeTime += v;
    }

    int Torchlight::getFrames(){
        return _frames;
    }
                
    void Torchlight::setFrames(int v){
        _frames += v;
    }


}
