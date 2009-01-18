#include "settings.h"

#include <QtXml>

Settings::Settings( QWidget *parent ) : QDialog( parent ) {

  QCoreApplication::setOrganizationDomain( "ayoy.net" );
  qApp->installTranslator( &translator );

  ui.setupUi( this );
  ui.languageCombo->setItemData( 0, "en" );
  createLanguageMenu();
  QIntValidator *portValidator= new QIntValidator( 1, 65535, this );
  ui.portEdit->setValidator( portValidator );
  proxy.setType( QNetworkProxy::NoProxy );
  if ( proxy.type() != QNetworkProxy::NoProxy ) {
    ui.proxyBox->setChecked( true );
    ui.hostEdit->setEnabled( true );
    ui.portEdit->setEnabled( true );
  }
  ui.hostEdit->setText( proxy.hostName() );
  if ( proxy.port() ) {
    ui.portEdit->setText( QString::number( proxy.port() ) );
  }
  connect( ui.languageCombo, SIGNAL( currentIndexChanged( int )), this, SLOT( switchLanguage( int ) ) );
}

Settings::~Settings() {}

void Settings::accept() {
  if ( ui.proxyBox->isChecked() ) {
    proxy.setType( QNetworkProxy::HttpProxy );
    proxy.setHostName( ui.hostEdit->text() );
    proxy.setPort( ui.portEdit->text().toInt() );
  } else {
    proxy.setType( QNetworkProxy::NoProxy );
  }
  QNetworkProxy::setApplicationProxy( proxy );
  saveConfig();
  QDialog::accept();
}

bool createConfigFile() {
  return true;
}

bool Settings::loadConfig() {
  QSettings settings( "ayoy", "qTwitter" );

  settings.beginGroup( "General" );
  ui.refreshCombo->setCurrentIndex( settings.value( "refresh" ).toInt() );
  ui.languageCombo->setCurrentIndex( settings.value( "languge", 1 ).toInt() );
  settings.endGroup();
  settings.beginGroup( "Network" );
  settings.beginGroup( "Proxy" );
  ui.proxyBox->setCheckState( (Qt::CheckState)settings.value( "enabled" ).toInt() );
  ui.hostEdit->setText( settings.value( "host" ).toString() );
  ui.portEdit->setText( settings.value( "port" ).toString() );
  settings.endGroup();
  settings.endGroup();

  return true;
}

bool Settings::saveConfig() {
  QSettings settings( "ayoy", "qTwitter" );

  settings.beginGroup( "General" );
  settings.setValue( "refresh", ui.refreshCombo->currentIndex() );
  settings.setValue( "language", ui.languageCombo->currentIndex() );
  settings.endGroup();
  settings.beginGroup( "Network" );
  settings.beginGroup( "Proxy" );
  settings.setValue( "enabled", ui.proxyBox->checkState() );
  settings.setValue( "host", ui.hostEdit->text() );
  settings.setValue( "port", ui.portEdit->text() );
  settings.endGroup();
  settings.endGroup();

  return true;
}

QString Settings::stateForXML ( QCheckBox *checkBox ) {
  if ( checkBox->checkState() == Qt::Checked ) {
      return "1";
  }
  return "0";
}

QDir Settings::directoryOf(const QString &subdir)
{
    QDir dir(QApplication::applicationDirPath());

#if defined(Q_OS_WIN)
    if (dir.dirName().toLower() == "debug"
            || dir.dirName().toLower() == "release")
        dir.cdUp();
#elif defined(Q_OS_MAC)
    if (dir.dirName() == "MacOS") {
        dir.cdUp();
        dir.cdUp();
        dir.cdUp();
    }
#endif
    dir.cd(subdir);
    return dir;
}

void Settings::switchLanguage( int index )
{
    QString locale = ui.languageCombo->itemData( index ).toString();
    QString qmPath = directoryOf("loc").absolutePath();
    qDebug() << "switching locale to" << locale << "from" << qmPath;
    translator.load( "qtwitter_" + locale, qmPath);
    retranslateUi();
}

void Settings::createLanguageMenu()
{
    QDir qmDir = directoryOf("loc");
    QStringList fileNames = qmDir.entryList(QStringList("qtwitter_*.qm"));
    //ui.languageCombo->addItem( "English", "en" );
    for (int i = 0; i < fileNames.size(); ++i) {
        QString locale = fileNames[i];
        locale.remove(0, locale.indexOf('_') + 1);
        locale.chop(3);

        QTranslator translator;
        translator.load(fileNames[i], qmDir.absolutePath());
        QString language = translator.translate("Settings", "English");

        ui.languageCombo->addItem( language, locale );
        //if (language == "English")
        //    action->setChecked(true);
    }
}

void Settings::retranslateUi() {
  ui.label->setText( tr("Refresh every") );
  ui.label_2->setText( tr("minutes") );
  ui.label_3->setText( tr("Language") );
}
