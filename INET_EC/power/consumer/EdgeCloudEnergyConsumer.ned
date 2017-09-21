//Created by LARRY

package inet.power.consumer;

import inet.power.base.EpEnergyConsumerBase;


simple EdgeCloudEnergyConsumer extends EpEnergyConsumerBase
{
    parameters:
        string energySourceModule = default("^.energyStorage"); // module path of energy source
        string serviceTableModule;
        //volatile double powerConsumption @unit(W); // amount of power consumed in consumption mode
        volatile double consumptionInterval @unit(s); // time interval for consumption mode
        //volatile double sleepInterval @unit(s); // time interval for sleep mode
        double consumptionPerMb;
        double consumptionPerMips;
        @class(EdgeCloudEnergyConsumer);
}
