#ifndef SARIBBONWIDGET_H
#define SARIBBONWIDGET_H
#include "SARibbonGlobal.h"
#include <QWidget>

class SARibbonBar;
class QScreen;
class SARibbonSystemButtonBar;
/**
 * @brief 带SARibbonBar的Widget
 *
 * @note 注意，SARibbonWidget利用了布局来把ribbonbar放到最顶部，不要给此widget添加布局，否则会导致布局异常，
 * 正确的做法是把布局的窗口通过setWidget设置进SARibbonWidget
 *
 */
class SA_RIBBON_EXPORT SARibbonWidget : public QWidget
{
	Q_OBJECT
	SA_RIBBON_DECLARE_PRIVATE(SARibbonWidget)
	friend class SARibbonBar;
	Q_PROPERTY(SARibbonTheme ribbonTheme READ ribbonTheme WRITE setRibbonTheme)

public:
	explicit SARibbonWidget(QWidget* parent = nullptr);
	~SARibbonWidget();
	// 返回SARibbonBar
	SARibbonBar* ribbonBar() const;
	// 设置ribbonbar
	void setRibbonBar(SARibbonBar* bar);

	// 注意主题在构造函数设置主题会不完全生效，使用QTimer投放到队列最后执行即可
    // QTimer::singleShot(0, this, [ this ]() { this->setRibbonTheme(SARibbonTheme::RibbonThemeDark); });
	void setRibbonTheme(SARibbonTheme theme);
	SARibbonTheme ribbonTheme() const;
	// 判断当前是否使用ribbon模式
	bool isUseRibbon() const;
    // 设置窗口
	void setWidget(QWidget* w);
	QWidget* widget() const;
    //
    QWidget* takeWidget();
private Q_SLOTS:
	void onPrimaryScreenChanged(QScreen* screen);
};
/**
 * @brief 全局的设置ribbon theme函数
 *
 * 之所以提供此函数，是因为在某些情况下，SARibbonBar不用在SARibbonMainWindow情况下的时候，也需要设置主题，
 * 但主题设置是在SARibbonMainWindow下的为了能在非SARibbonMainWindow下也能设置主题，这里提供@sa sa_set_ribbon_theme函数，
 * 可以这样使用：
 * @code
 * @endcode
 *
 * @param w
 * @param theme
 */
void SA_RIBBON_EXPORT sa_set_ribbon_theme(QWidget* w, SARibbonTheme theme);
/**
 * @brief 根据主题应用/恢复SARibbonBar的整体布局参数
 *
 * 部分主题（如RibbonThemeModernBlue）除了qss外，还需要配套的布局参数才能达到预期效果，
 * 此函数把这些参数内置到主题切换中，且只影响ModernBlue主题：
 * - 切入RibbonThemeModernBlue时，先备份当前布局，再应用ModernBlue的标题栏布局（隐藏标题、tab及pannel居中等），
 *   不改变ribbon风格及pannel内部元素的尺寸
 * - 从ModernBlue切出到其他主题时，恢复切入前备份的布局
 * - 其他主题之间的切换不做任何布局改动
 *
 * @param bar
 * @param theme
 */
void SA_RIBBON_EXPORT sa_apply_ribbon_theme_layout(SARibbonBar* bar, SARibbonTheme theme);
/**
 * @brief 配置主题相关的运行时布局参数（tabbar 居中、窗口按钮尺寸等）
 *
 * @param bar
 * @param theme
 * @param windowButtonGroup 可为 nullptr（SARibbonWidget 场景下无系统按钮栏）
 */
void SA_RIBBON_EXPORT sa_configure_ribbon_theme_options(SARibbonBar* bar,
                                                        SARibbonTheme theme,
                                                        SARibbonSystemButtonBar* windowButtonGroup = nullptr);
#endif  // SARIBBONWIDGET_H
