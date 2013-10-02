#include "voreenapplicationqt5.h"

using std::string;


namespace voreen {

VoreenApplicationQt5* VoreenApplicationQt5::qtApp_ = 0;
const std::string VoreenApplicationQt5::loggerCat_ = "voreenqt.VoreenApplicationQt5";

VoreenApplicationQt5::VoreenApplicationQt5(const std::string& name, const std::string& displayName, const std::string& description,
                                         int argc, char** argv, ApplicationFeatures appType)
    : VoreenApplication(name, displayName, description, argc, argv, appType)
    , resetApplicationSettingsButton_("resetApplicationSettings", "Reset Window Settings")
    , scaleProcessorFontSizeProperty_("scaleProcessorFontSize","Scale Processor Fonts:",100,50,150)
    , mainWindow_(0)
    , clearSettings_(false)
{
    qApp->setOrganizationName("Voreen");
    qApp->setOrganizationDomain("voreen.org");
    qApp->setApplicationName(displayName.c_str());

    addProperty(resetApplicationSettingsButton_);
    resetApplicationSettingsButton_.onClick(
        CallMemberAction<VoreenApplicationQt5>(this, &VoreenApplicationQt5::queryResetApplicationSettings));
    resetApplicationSettingsButton_.setGroupID("user-interface");
    //network editor properties
    addProperty(scaleProcessorFontSizeProperty_);
        scaleProcessorFontSizeProperty_.setGroupID("nwe");
    setPropertyGroupGuiName("nwe","Network Editor");

    qtApp_ = this;
}

VoreenApplicationQt5::~VoreenApplicationQt5() {

}

void VoreenApplicationQt5::initialize() throw (VoreenException) {
    VoreenApplication::initialize();
}

void VoreenApplicationQt5::deinitialize() throw (VoreenException) {
    VoreenApplication::deinitialize();
}

void VoreenApplicationQt5::initializeGL() throw (VoreenException) {
    VoreenApplication::initializeGL();
}

void VoreenApplicationQt5::deinitializeGL() throw (VoreenException) {
    VoreenApplication::deinitializeGL();
}

void VoreenApplicationQt5::setMainWindow(QMainWindow* mainWindow) {
    mainWindow_ = mainWindow;
}

QMainWindow* VoreenApplicationQt5::getMainWindow() const {
    return mainWindow_;
}

VoreenApplicationQt5* VoreenApplicationQt5::qtApp() {
    return qtApp_;
}

tgt::Timer* VoreenApplicationQt5::createTimer(tgt::EventHandler* handler) const {
    return new tgt::QtTimer(handler);
}

void VoreenApplicationQt5::resetApplicationSettings() {
    QSettings settings;
    settings.clear();
    clearSettings_ = true;
}

int VoreenApplicationQt5::getProcessorFontScale() const {
    return scaleProcessorFontSizeProperty_.get();
}

void VoreenApplicationQt5::queryResetApplicationSettings() {
    QMessageBox msgBox(mainWindow_);
    msgBox.setWindowTitle(QApplication::tr("Reset Windows Settings"));
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setText(QApplication::tr("This will reset the complete window configuration as well as the default paths."));
    msgBox.setInformativeText(QApplication::tr("Do you want to proceed?"));
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    int ret = msgBox.exec();
    if (ret == QMessageBox::Ok) {
        resetApplicationSettings();
        QMessageBox::information(mainWindow_, QApplication::tr("Window Settings Restored"),
            QApplication::tr("All window settings have been restored. "
            "Please restart the application for the changes to take effect."));
    }
}

} // namespace

