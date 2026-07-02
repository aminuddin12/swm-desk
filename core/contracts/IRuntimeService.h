#ifndef IRUNTIMESERVICE_H
#define IRUNTIMESERVICE_H

class IRuntimeService {
public:
    virtual ~IRuntimeService() = default;
    virtual void initialize() = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void shutdown() = 0;
};

#endif
