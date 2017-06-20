// Copyright Alan (AJ) Pryor, Jr. 2017
// Transcribed from MATLAB code by Colin Ophus
// PRISM is distributed under the GNU General Public License (GPL)
// If you use PRISM, we ask that you cite the following papers:

#ifndef PRISM_QTHREADS_H
#define PRISM_QTHREADS_H
#include <QThread>
#include "prism_progressbar.h"
#include "ArrayND.h"
#include "params.h"
#include "defines.h"
#include "prismmainwindow.h"

// defines QThread derived classes for running work from the PRISM GUI
class PRISMThread : public QThread {
    Q_OBJECT
    friend class PRISMMainWindow;
public:
    explicit PRISMThread(PRISMMainWindow *_parent, prism_progressbar *progressbar);
    virtual ~PRISMThread();
protected:
    Prismatic::Metadata<PRISMATIC_FLOAT_PRECISION> meta;
    PRISMMainWindow *parent;
    prism_progressbar *progressbar;
signals:
    void potentialCalculated();
    void signalErrorReadingAtomsDialog();
    void outputCalculated();
};

class PotentialThread : public PRISMThread {
    Q_OBJECT
    void run() Q_DECL_OVERRIDE;
    friend class PRISMMainWindow;
public:
    explicit PotentialThread(PRISMMainWindow *_parent, prism_progressbar *progressbar);
    virtual ~PotentialThread();
};

class ProbeThread : public PRISMThread {
    Q_OBJECT
    void run() Q_DECL_OVERRIDE;
    friend class PRISMMainWindow;
public:
    explicit ProbeThread(PRISMMainWindow *_parent, PRISMATIC_FLOAT_PRECISION _X, PRISMATIC_FLOAT_PRECISION _Y, prism_progressbar *progressbar, bool use_log_scale = false);
    virtual ~ProbeThread();
signals:
    void signalProbeK_PRISM(Prismatic::Array2D<PRISMATIC_FLOAT_PRECISION>);
    void signalProbeR_PRISM(Prismatic::Array2D<PRISMATIC_FLOAT_PRECISION>);
    void signalProbeK_Multislice(Prismatic::Array2D<PRISMATIC_FLOAT_PRECISION>);
    void signalProbeR_Multislice(Prismatic::Array2D<PRISMATIC_FLOAT_PRECISION>);
    void signalProbe_diffK(Prismatic::Array2D<PRISMATIC_FLOAT_PRECISION>, Prismatic::Array2D<PRISMATIC_FLOAT_PRECISION>);
    void signalProbe_diffR(Prismatic::Array2D<PRISMATIC_FLOAT_PRECISION>, Prismatic::Array2D<PRISMATIC_FLOAT_PRECISION>);
    void signal_pearsonReal(QString str);
    void signal_pearsonK(QString str);
    void signal_RReal(QString str);
    void signal_RK(QString str);
private:
    PRISMATIC_FLOAT_PRECISION X, Y;
    bool use_log_scale;
};

class FullPRISMCalcThread : public PRISMThread {
    Q_OBJECT
    void run() Q_DECL_OVERRIDE;
    friend class PRISMMainWindow;
public:
    explicit FullPRISMCalcThread(PRISMMainWindow *_parent, prism_progressbar *progressbar);
    virtual ~FullPRISMCalcThread();
signals:
    void signalTitle(const QString str);
};

class FullMultisliceCalcThread : public PRISMThread {
    Q_OBJECT
    void run() Q_DECL_OVERRIDE;
    friend class PRISMMainWindow;
public:
    explicit FullMultisliceCalcThread(PRISMMainWindow *_parent, prism_progressbar *progressbar);
    virtual ~FullMultisliceCalcThread();
signals:
    void signalTitle(const QString str);
};

#endif // PRISM_QTHREADS_H
