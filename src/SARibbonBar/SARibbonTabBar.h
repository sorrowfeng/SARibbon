#ifndef SARIBBONTABBAR_H
#define SARIBBONTABBAR_H
#include "SARibbonGlobal.h"
#include <QTabBar>
#include <QMargins>

/**
 * @brief The SARibbonTabBar class
 */
class SA_RIBBON_EXPORT SARibbonTabBar : public QTabBar
{
	Q_OBJECT
public:
	explicit SARibbonTabBar(QWidget* parent = nullptr);
    ~SARibbonTabBar();
	const QMargins& tabMargin() const;
	void setTabMargin(const QMargins& tabMargin);
	// 0 表示使用 tabbar 默认高度
	void setTabItemHeight(int height);
	int tabItemHeight() const;

protected:
	QSize tabSizeHint(int index) const;

private:
	QMargins m_tabMargin;
	int mTabItemHeight { 0 };
};

#endif  // SARIBBONTABBAR_H
