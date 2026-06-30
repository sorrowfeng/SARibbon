#include "ModernBlueStyleWindow.h"

#include "SARibbonBar.h"
#include "SARibbonButtonGroupWidget.h"
#include "SARibbonCategory.h"
#include "SARibbonControlButton.h"
#include "SARibbonPannel.h"

#include <QAbstractButton>
#include <QAction>
#include <QActionGroup>
#include <QApplication>
#include <QCheckBox>
#include <QFrame>
#include <QGridLayout>
#include <QLayout>
#include <QPainter>
#include <QPixmap>
#include <QRadioButton>
#include <QStringList>
#include <QTimer>
#include <QToolButton>
#include <QVBoxLayout>

ModernBlueStyleWindow::ModernBlueStyleWindow(QWidget* parent) : SARibbonMainWindow(parent)
{
	setWindowTitle(QStringLiteral("Modern Blue Style Example"));
	setWindowIcon(createGlyphIcon(QStringLiteral("S"), QColor(36, 169, 232), Qt::white));
	resize(1366, 230);

	buildRibbon();

	QFrame* page = new QFrame(this);
	page->setObjectName(QStringLiteral("ModernBlueExamplePage"));
	page->setStyleSheet(QStringLiteral("#ModernBlueExamplePage{background:#eef3f8;}"));
	setCentralWidget(page);

	QTimer::singleShot(0, this, [ this ]() {
		setRibbonTheme(SARibbonTheme::RibbonThemeModernBlue);
		ribbonBar()->setPannelAlignment(SARibbonAlignment::AlignCenter);
		ribbonBar()->setRibbonAlignment(SARibbonAlignment::AlignCenter);
		ribbonBar()->updateRibbonGeometry();
	});
}

void ModernBlueStyleWindow::buildRibbon()
{
	SARibbonBar* ribbon = ribbonBar();
	ribbon->setRibbonStyle(SARibbonBar::RibbonStyleCompactThreeRow);
	ribbon->setTitleVisible(false);
	ribbon->setTitleBarHeight(48);
	ribbon->setTabBarHeight(30);
	ribbon->setCategoryHeight(100);
	ribbon->setEnableShowPannelTitle(false);
	ribbon->setPannelSpacing(8);
	ribbon->setPannelToolButtonIconSize(QSize(24, 24));
	ribbon->setButtonTextEllipsisAspectFactor(2.2);
	ribbon->setApplicationButton(createBrandButton(ribbon));
	ribbon->setRibbonAlignment(SARibbonAlignment::AlignCenter);
	ribbon->setPannelAlignment(SARibbonAlignment::AlignCenter);
	ribbon->showMinimumModeButton(true);

	SARibbonButtonGroupWidget* rightGroup = ribbon->rightButtonGroup();
	rightGroup->setObjectName(QStringLiteral("ModernBlueTitleButtonGroup"));
	rightGroup->setIconSize(QSize(16, 16));
	if (QLayout* titleButtonLayout = rightGroup->layout()) {
		titleButtonLayout->setContentsMargins(0, 0, 0, 0);
		titleButtonLayout->setSpacing(4);
	}
	if (QAction* minimumAction = ribbon->minimumModeAction()) {
		minimumAction->setIcon(QIcon(QStringLiteral(":/SARibbon/image/resource/Titlebar_Shade.png")));
		if (SARibbonControlButton* button = rightGroup->actionToRibbonControlToolButton(minimumAction)) {
			button->setFixedSize(32, 30);
		}
		connect(ribbon, &SARibbonBar::ribbonModeChanged, this, [ minimumAction ](SARibbonBar::RibbonMode mode) {
			const QString iconPath = (mode == SARibbonBar::MinimumRibbonMode)
			                             ? QStringLiteral(":/SARibbon/image/resource/Titlebar_Unshade.png")
			                             : QStringLiteral(":/SARibbon/image/resource/Titlebar_Shade.png");
			minimumAction->setIcon(QIcon(iconPath));
		});
	}
	QAction* helpAction = new QAction(createHelpIcon(), QString(), this);
	helpAction->setToolTip(QStringLiteral("帮助"));
	rightGroup->addAction(helpAction);
	if (SARibbonControlButton* button = rightGroup->actionToRibbonControlToolButton(helpAction)) {
		button->setFixedSize(32, 30);
	}

	buildMainCategory(ribbon);
	buildSecondaryCategory(ribbon);
	ribbon->setCurrentIndex(0);
}

void ModernBlueStyleWindow::buildMainCategory(SARibbonBar* ribbon)
{
	SARibbonCategory* main = ribbon->addCategoryPage(QStringLiteral("主要"));

	SARibbonPannel* connectPanel = main->addPannel(QStringLiteral("连接"));
	connectPanel->addLargeAction(createAction(QStringLiteral("连接"), createGlyphIcon(QStringLiteral("G"), QColor(78, 184, 246), Qt::white)));
	connectPanel->addLargeAction(createAction(QStringLiteral("窗口可见性"), createGlyphIcon(QStringLiteral("W"), QColor(78, 184, 246), Qt::white)));
	connectPanel->addSeparator();
	connectPanel->addLargeAction(createAction(QStringLiteral("拖动控制"), createGlyphIcon(QStringLiteral("M"), QColor(78, 184, 246), Qt::white)));

	SARibbonPannel* viewPanel = main->addPannel(QStringLiteral("视图"));
	viewPanel->addSmallAction(createAction(QStringLiteral("左视图"), createGlyphIcon(QStringLiteral("L"), QColor(74, 162, 226), Qt::white)));
	viewPanel->addSmallAction(createAction(QStringLiteral("右视图"), createGlyphIcon(QStringLiteral("R"), QColor(74, 162, 226), Qt::white)));
	viewPanel->addSmallAction(createAction(QStringLiteral("适应视图"), createGlyphIcon(QStringLiteral("F"), QColor(74, 162, 226), Qt::white)));

	SARibbonPannel* handPanel = main->addPannel(QStringLiteral("手动"));
	QActionGroup* handGroup = new QActionGroup(this);
	QAction* leftHand = createAction(QStringLiteral("左手"), createGlyphIcon(QStringLiteral("L"), QColor(241, 164, 139), Qt::white), true);
	QAction* rightHand = createAction(QStringLiteral("右手"), createGlyphIcon(QStringLiteral("R"), QColor(241, 164, 139), Qt::white), true);
	handGroup->addAction(leftHand);
	handGroup->addAction(rightHand);
	leftHand->setChecked(true);
	handPanel->addLargeAction(leftHand);
	handPanel->addLargeAction(rightHand);

	SARibbonPannel* devicePanel = main->addPannel(QStringLiteral("设备"));
	QActionGroup* deviceGroup = new QActionGroup(this);
	QAction* device1 = createAction(QStringLiteral("Dex-01"), createGlyphIcon(QStringLiteral("D1"), QColor(65, 80, 95), Qt::white), true);
	QAction* device2 = createAction(QStringLiteral("Dex-02"), createGlyphIcon(QStringLiteral("D2"), QColor(65, 80, 95), Qt::white), true);
	deviceGroup->addAction(device1);
	deviceGroup->addAction(device2);
	device1->setChecked(true);
	devicePanel->addLargeAction(device1);
	devicePanel->addLargeAction(device2);

	SARibbonPannel* executionPanel = main->addPannel(QStringLiteral("执行"));
	executionPanel->addLargeWidget(createExecutionOptions(executionPanel));

	SARibbonPannel* statePanel = main->addPannel(QStringLiteral("状态"));
	statePanel->addLargeWidget(createStateOptions(statePanel));
}

void ModernBlueStyleWindow::buildSecondaryCategory(SARibbonBar* ribbon)
{
	SARibbonCategory* other = ribbon->addCategoryPage(QStringLiteral("其他"));
	SARibbonPannel* otherPanel = other->addPannel(QStringLiteral("常用"));
	otherPanel->addLargeAction(createAction(QStringLiteral("设置"), createGlyphIcon(QStringLiteral("S"), QColor(54, 132, 204), Qt::white)));
	otherPanel->addLargeAction(createAction(QStringLiteral("日志"), createGlyphIcon(QStringLiteral("L"), QColor(54, 132, 204), Qt::white)));

	SARibbonCategory* expert = ribbon->addCategoryPage(QStringLiteral("专家"));
	SARibbonPannel* expertPanel = expert->addPannel(QStringLiteral("调试"));
	expertPanel->addLargeAction(createAction(QStringLiteral("标定"), createGlyphIcon(QStringLiteral("C"), QColor(54, 132, 204), Qt::white)));
	expertPanel->addLargeAction(createAction(QStringLiteral("诊断"), createGlyphIcon(QStringLiteral("D"), QColor(54, 132, 204), Qt::white)));
}

QAction* ModernBlueStyleWindow::createAction(const QString& text, const QIcon& icon, bool checkable)
{
	QAction* action = new QAction(icon, text, this);
	action->setIconText(text);
	action->setToolTip(text);
	action->setCheckable(checkable);
	connect(action, &QAction::triggered, this, [ this, text ]() {
		setWindowTitle(QStringLiteral("Modern Blue Style Example - %1").arg(text));
	});
	return action;
}

QWidget* ModernBlueStyleWindow::createExecutionOptions(SARibbonPannel* parent)
{
	QWidget* widget = new QWidget(parent);
	widget->setObjectName(QStringLiteral("ExecutionOptions"));
	QVBoxLayout* layout = new QVBoxLayout(widget);
	layout->setContentsMargins(6, 4, 6, 4);
	layout->setSpacing(4);

	QRadioButton* all = new QRadioButton(QStringLiteral("全部执行"), widget);
	QRadioButton* step = new QRadioButton(QStringLiteral("单步执行"), widget);
	all->setChecked(true);
	layout->addWidget(all);
	layout->addWidget(step);
	layout->addStretch();
	widget->setFixedSize(86, 64);
	return widget;
}

QWidget* ModernBlueStyleWindow::createStateOptions(SARibbonPannel* parent)
{
	QWidget* widget = new QWidget(parent);
	widget->setObjectName(QStringLiteral("StateOptions"));
	QGridLayout* layout = new QGridLayout(widget);
	layout->setContentsMargins(6, 3, 6, 3);
	layout->setHorizontalSpacing(10);
	layout->setVerticalSpacing(2);

	const QStringList labels = { QStringLiteral("使能关节"),
								 QStringLiteral("去使能关节"),
								 QStringLiteral("清除报警"),
								 QStringLiteral("定位回零"),
								 QStringLiteral("强制回零") };
	for (int i = 0; i < labels.size(); ++i) {
		QCheckBox* check = new QCheckBox(labels.at(i), widget);
		check->setChecked(i == 0);
		layout->addWidget(check, i / 3, i % 3);
	}
	widget->setFixedSize(300, 64);
	return widget;
}

QAbstractButton* ModernBlueStyleWindow::createBrandButton(SARibbonBar* ribbon)
{
	QToolButton* button = new QToolButton(ribbon);
	button->setObjectName(QStringLiteral("ModernBlueBrandButton"));
	button->setText(QStringLiteral("STYLE\nLAB"));
	button->setIcon(createGlyphIcon(QStringLiteral("S"), QColor(30, 148, 212), Qt::white));
	button->setIconSize(QSize(30, 30));
	button->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	button->setAutoRaise(true);
	button->setFixedWidth(126);
	button->setStyleSheet(QStringLiteral(
	    "QToolButton#ModernBlueBrandButton{background:transparent;border:none;color:#ffffff;font-weight:bold;text-align:left;}"
	    "QToolButton#ModernBlueBrandButton:hover{background:#1E94D4;}"));
	return button;
}

QIcon ModernBlueStyleWindow::createGlyphIcon(const QString& glyph, const QColor& background, const QColor& foreground)
{
	QPixmap pixmap(64, 64);
	pixmap.fill(Qt::transparent);

	QPainter painter(&pixmap);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setBrush(background);
	painter.setPen(Qt::NoPen);
	painter.drawRoundedRect(QRectF(6, 6, 52, 52), 12, 12);

	QFont font = qApp->font();
	font.setBold(true);
	font.setPixelSize(glyph.size() > 1 ? 20 : 30);
	painter.setFont(font);
	painter.setPen(foreground);
	painter.drawText(pixmap.rect(), Qt::AlignCenter, glyph);

	return QIcon(pixmap);
}

QIcon ModernBlueStyleWindow::createHelpIcon()
{
	QPixmap pixmap(32, 32);
	pixmap.fill(Qt::transparent);

	QPainter painter(&pixmap);
	painter.setRenderHint(QPainter::Antialiasing);
	QPen pen(QColor(220, 235, 255), 1.7);
	painter.setPen(pen);
	painter.setBrush(Qt::NoBrush);
	painter.drawEllipse(QRectF(9, 8, 14, 14));

	QFont font = qApp->font();
	font.setBold(true);
	font.setPixelSize(14);
	painter.setFont(font);
	painter.setPen(Qt::white);
	painter.drawText(QRectF(9, 7, 14, 16), Qt::AlignCenter, QStringLiteral("?"));
	return QIcon(pixmap);
}
