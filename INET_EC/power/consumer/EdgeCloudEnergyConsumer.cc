//Created by LARRY

#include "inet/power/consumer/EdgeCloudEnergyConsumer.h"
#include "inet/networklayer/ipv4/IIPv4ServiceTable.h"
#include "inet/common/ModuleAccess.h"

namespace inet {

namespace power {

Define_Module(EdgeCloudEnergyConsumer);

EdgeCloudEnergyConsumer::~EdgeCloudEnergyConsumer()
{
    cancelAndDelete(timer);
}

void EdgeCloudEnergyConsumer::initialize(int stage)
{
    if (stage == INITSTAGE_LOCAL) {
        const char *energySourceModule = par("energySourceModule");
        consumptionPerMb = par("consumptionPerMb");
        consumptionPerMips = par("consumptionPerMips");

        st = getModuleFromPar<IIPv4ServiceTable>(par("serviceTableModule"), this);
        energySource = dynamic_cast<IEpEnergySource *>(getModuleByPath(energySourceModule));
        if (!energySource)
            throw cRuntimeError("Energy source module '%s' not found", energySourceModule);
        timer = new cMessage("timer");
        updatePowerConsumption();
        scheduleIntervalTimer();
        energySource->addEnergyConsumer(this);
        WATCH(powerConsumption);
    }
}

void EdgeCloudEnergyConsumer::handleMessage(cMessage *message)
{
    if (message == timer) {
        //isSleeping = !isSleeping;
        updatePowerConsumption();
        scheduleIntervalTimer();
    }
    else
        throw cRuntimeError("Unknown message");
}

void EdgeCloudEnergyConsumer::updatePowerConsumption()
{
    powerConsumption = W(0);
    double edgeServiceConsumption = 0;
    EV<< "LARRY ~~~ st->getNumberOfService() = " << st->getNumberOfService() <<"\n";
    for(int i = 0; i < st->getNumberOfService(); i++){
        edgeServiceConsumption += (st->getServiceSize(i) + st->getServiceCacheSize(i))*consumptionPerMb + st->getServiceMips(i)*consumptionPerMips;
        EV<< "LARRY ~~~ st->getServiceSize("<<i<<") = " << st->getServiceSize(i) <<"\n";
        EV<< "LARRY ~~~ st->getServiceCacheSize("<<i<<") = " << st->getServiceCacheSize(i) <<"\n";
        EV<< "LARRY ~~~ st->getServiceMips("<<i<<") = " << st->getServiceMips(i) <<"\n";
        EV<< "----\n";
    }
    powerConsumption = W(edgeServiceConsumption);

    EV<< "LARRY ~~~ powerConsumption = " << powerConsumption <<"\n";

    emit(IEpEnergySource::powerConsumptionChangedSignal, powerConsumption.get());
}

void EdgeCloudEnergyConsumer::scheduleIntervalTimer()
{
    scheduleAt(simTime() + par("consumptionInterval"), timer);
}

} // namespace power

} // namespace inet

