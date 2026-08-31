#ifndef MODERNBLUESTYLEWINDOW_H
#define MODERNBLUESTYLEWINDOW_H

#include "SARibbonMainWindow.h"

#include <QColor>
#include <QIcon>
#include <QString>

class QAction;
class QAbstractButton;
class SARibbonBar;
class SARibbonPanel;
class QWidget;

class ModernBlueStyleWindow : public SARibbonMainWindow
{
public:
	explicit ModernBlueStyleWindow(QWidget* parent = nullptr);

private:
	void buildRibbon();
	void buildMainCategory(SARibbonBar* ribbon);
	void buildSecondaryCategory(SARibbonBar* ribbon);
	QAction* createAction(const QString& text, const QIcon& icon, bool checkable = false);
	QWidget* createExecutionOptions(SARibbonPanel* parent);
	QWidget* createStateOptions(SARibbonPanel* parent);
	QAbstractButton* createBrandButton(SARibbonBar* ribbon);
	static QIcon createGlyphIcon(const QString& glyph, const QColor& background, const QColor& foreground);
};

#endif  // MODERNBLUESTYLEWINDOW_H
