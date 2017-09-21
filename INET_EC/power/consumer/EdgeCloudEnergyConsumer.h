// Created by LARRY

#ifndef __INET_EDGECLOUDENERGYCONSUMER_H
#define __INET_EDGECLOUDENERGYCONSUMER_H

#include "inet/power/contract/IEpEnergyConsumer.h"
#include "inet/power/contract/IEpEnergySource.h"

namespace inet {

class IIPv4ServiceTable;

namespace power {

/**
 * This class implements a simple power consumer for edge/cache service
 *
 * See the corresponding NED file for more details.
 *
 * @author LARRY
 */
class INET_API EdgeCloudEnergyConsumer : public cSimpleModule, public IEpEnergyConsumer
{
  protected:
    // parameters
    IEpEnergySource *energySource = nullptr;
    cMessage *timer = nullptr;
    IIPv4ServiceTable *st = nullptr;

    // state
    W powerConsumption = W(NaN);
    double consumptionPerMb = 0;
    double consumptionPerMips = 0;
  protected:
    virtual void initialize(int stage) override;
    virtual void handleMessage(cMessage *message) override;

    virtual void updatePowerConsumption();
    virtual void scheduleIntervalTimer();

  public:
    virtual ~EdgeCloudEnergyConsumer();

    virtual IEnergySource *getEnergySource() const override { return energySource; }
    virtual W getPowerConsumption() const override { return powerConsumption; }
};

} // namespace power

} // namespace inet

#endif // ifndef __INET_EDGECLOUDENERGYCONSUMER_H

