#ifndef VRNAPPLICATIONQT5_H
#define VRNAPPLICATIONQT5_H

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMessageBox>
#include <QSettings>

#include "voreen/core/voreenapplication.h"
#include "voreen/core/properties/buttonproperty.h"

//includes for networkeditor
#include "voreen/core/properties/intproperty.h"

#include "tgt/qt/qttimer.h"

namespace voreen {

class VoreenApplicationQt5 : public VoreenApplication {
public:
    VoreenApplicationQt5(const std::string& name, const std::string& displayName, const std::string& description,
                        int argc, char** argv, ApplicationFeatures appType = APP_DEFAULT);
    ~VoreenApplicationQt5();

    virtual void initialize() throw (VoreenException);
    virtual void deinitialize() throw (VoreenException);

    virtual void initializeGL() throw (VoreenException);
    virtual void deinitializeGL() throw (VoreenException);

    /**
     * Allows access to the global instance of this class.
     */
    static VoreenApplicationQt5* qtApp();

    void setMainWindow(QMainWindow* mainWindow);

    QMainWindow* getMainWindow() const;

    /**
     * Creates a tgt::QtTimer.
     *
     * @param handler The event handler that will be used
     *  for broadcasting the timer events. Must not be null.
     */
    virtual tgt::Timer* createTimer(tgt::EventHandler* handler) const;

    /**
     * Clears the QSettings used by this application.
     */
    virtual void resetApplicationSettings();

    /**
     * Returns the the scaleProcessorFontSizeProperty value.
     */
    virtual int getProcessorFontScale() const;

    /**
     * Registers a widget to receive touch events.  Default implementation does nothing.
     */
    virtual void sendTouchEventsTo(QWidget *wid) {}

private:
    /**
     * Queries the user whether the Qt application settings should
     * be reset and calls resetApplicationSettings() on positive answer.
     */
    void queryResetApplicationSettings();

    /// Button for resetting the Qt application settings (displayed by the VoreenVE settings dialog).
    ButtonProperty resetApplicationSettingsButton_;

    ///Properties for the network editor
    IntProperty scaleProcessorFontSizeProperty_;

    static VoreenApplicationQt5* qtApp_;
    QMainWindow* mainWindow_;

    /// indicates that the application settings have to be cleared on application destruction
    bool clearSettings_;

    static const std::string loggerCat_;

};

} // namespace

#endif //VRNAPPLICATIONQT5_H
