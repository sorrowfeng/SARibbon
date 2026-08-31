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
	Q_PROPERTY(SARibbonTheme ribbonTheme READ ribbonTheme WRITE setRibbonTheme NOTIFY ribbonThemeChanged)

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
Q_SIGNALS:
	/// Emitted when ribbon theme changes
	void ribbonThemeChanged(SARibbonTheme theme);
};

/**
 * \if ENGLISH
 * @brief Apply or restore the overall layout parameters of SARibbonBar according to the theme
 *
 * Some themes (such as RibbonThemeModernBlue) require matching layout parameters in addition to qss.
 * This function builds these parameters into the theme switch and only affects the ModernBlue theme:
 * - When switching to RibbonThemeModernBlue, the current layout is backed up first, then the ModernBlue
 *   titlebar layout is applied (hide title, center tab and panel, etc.), without changing the ribbon
 *   style and the size of the internal elements of the panel
 * - When switching from ModernBlue to other themes, the backed-up layout is restored
 * - Switching between other themes does not change the layout
 *
 * @param bar The ribbon bar
 * @param theme The theme to apply
 * \endif
 *
 * \if CHINESE
 * @brief 根据主题应用/恢复SARibbonBar的整体布局参数
 *
 * 部分主题（如RibbonThemeModernBlue）除了qss外，还需要配套的布局参数才能达到预期效果，
 * 此函数把这些参数内置到主题切换中，且只影响ModernBlue主题：
 * - 切入RibbonThemeModernBlue时，先备份当前布局，再应用ModernBlue的标题栏布局（隐藏标题、tab及panel居中等），
 *   不改变ribbon风格及panel内部元素的尺寸
 * - 从ModernBlue切出到其他主题时，恢复切入前备份的布局
 * - 其他主题之间的切换不做任何布局改动
 *
 * @param bar ribbon栏
 * @param theme 主题
 * \endif
 */
void SA_RIBBON_EXPORT sa_apply_ribbon_theme_layout(SARibbonBar* bar, SARibbonTheme theme);

/**
 * \if ENGLISH
 * @brief Configure theme-related runtime layout parameters (tabbar centering, window button size, etc.)
 * @param bar The ribbon bar
 * @param theme The theme to apply
 * @param windowButtonGroup Can be nullptr (no system button bar in SARibbonWidget scenarios)
 * \endif
 *
 * \if CHINESE
 * @brief 配置主题相关的运行时布局参数（tabbar 居中、窗口按钮尺寸等）
 * @param bar ribbon栏
 * @param theme 主题
 * @param windowButtonGroup 可为 nullptr（SARibbonWidget 场景下无系统按钮栏）
 * \endif
 */
void SA_RIBBON_EXPORT sa_configure_ribbon_theme_options(SARibbonBar* bar,
                                                        SARibbonTheme theme,
                                                        SARibbonSystemButtonBar* windowButtonGroup = nullptr);

#endif  // SARIBBONWIDGET_H
