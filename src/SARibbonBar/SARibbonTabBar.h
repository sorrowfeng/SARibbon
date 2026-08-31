#ifndef SARIBBONTABBAR_H
#define SARIBBONTABBAR_H
#include "SARibbonGlobal.h"
#include <QTabBar>
#include <QMargins>

/**
 * \if ENGLISH
 * @brief Ribbon tab bar widget for SARibbon framework
 * \endif
 *
 * \if CHINESE
 * @brief SARibbon框架的Ribbon标签栏部件
 * \endif
 */
class SA_RIBBON_EXPORT SARibbonTabBar : public QTabBar
{
	Q_OBJECT
public:
	/// Constructs a SARibbonTabBar instance
	explicit SARibbonTabBar(QWidget* parent = nullptr);
    /// Destructor
    ~SARibbonTabBar();
	/// Gets the tab margin
	const QMargins& tabMargin() const;
	/// Sets the tab margin
	void setTabMargin(const QMargins& tabMargin);
	/// Set the tab item height, 0 means using the default tabbar height
	void setTabItemHeight(int height);
	/// Get the tab item height
	int tabItemHeight() const;

protected:
	/// Estimates the size of a tab
	QSize tabSizeHint(int index) const;

private:
	QMargins m_tabMargin;
	int mTabItemHeight { 0 };
};

#endif  // SARIBBONTABBAR_H
