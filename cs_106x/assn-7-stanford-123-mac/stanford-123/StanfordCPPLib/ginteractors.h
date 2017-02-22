/*
 * File: ginteractors.h
 * --------------------
 * This file exports a hierarchy of graphical interactors similar to those
 * provided in the Java Swing libraries.
 */

#ifndef _ginteractors_h
#define _ginteractors_h

#include "gobjects.h"
#include "gtypes.h"
#include "gwindow.h"
#include "vector.h"

/*
 * Class: GInteractor
 * ------------------
 * This abstract class represents the superclass for all interactors
 * that can be displayed in a graphical window.  In most applications,
 * interactors will be added to a control strip along one of the sides
 * of the <code>GWindow</code>, but they can also be placed in specific
 * positions just like any other <code>GObject</code>.
 */

class GInteractor : public GObject {

public:

/*
 * Method: setActionCommand
 * Usage: interactor.setActionCommand(cmd);
 * ----------------------------------------
 * Sets the action command to the indicated string.  If the string is not
 * empty, activating the interactor generates a <code>GActionEvent</code>.
 */

   void setActionCommand(std::string cmd);

/*
 * Method: getActionCommand
 * Usage: string cmd = interactor.getActionCommand();
 * --------------------------------------------------
 * Returns the action command associated with the interactor.
 */

   std::string getActionCommand();

/*
 * Method: setSize
 * Usage: interactor.setSize(size);
 *        interactor.setSize(width, height);
 * -----------------------------------------
 * Changes the size of the interactor to the specified width and height.
 */

   void setSize(const GDimension & size);
   void setSize(double width, double height);

/*
 * Method: setBounds
 * Usage: interactor.setBounds(rect);
 *        interactor.setBounds(x, y, width, height);
 * -------------------------------------------------
 * Changes the bounds of the interactor to the specified values.
 */

   void setBounds(const GRectangle & size);
   void setBounds(double x, double y, double width, double height);

/* Prototypes for the virtual methods */

   virtual GRectangle getBounds() const;

protected:

   GInteractor();

   std::string actionCommand;

};

/*
 * Class: GButton
 * --------------
 * This class represents an onscreen button.
 */

class GButton : public GInteractor {

public:

/*
 * Constructor: GButton
 * Usage: GButton button(label);
 * -----------------------------
 * Creates a <code>GButton</code> with the specified label.  This
 * constructor also sets the action command for the button to the
 * label string.
 */

   GButton(std::string label);

/* Prototypes for the virtual methods */

   virtual std::string getType() const;
   virtual std::string toString() const;

private:
   std::string label;

};

/*
 * Class: GCheckBox
 * ----------------
 * This class represents an onscreen checkbox.
 */

class GCheckBox : public GInteractor {

public:

/*
 * Constructor: GCheckBox
 * Usage: GCheckBox chkbox(label);
 * -------------------------------
 * Creates a <code>GCheckBox</code> with the specified label.  In contrast
 * to the <code>GButton</code> constructor, this constructor does not set
 * an action command.
 */

   GCheckBox(std::string label);

/*
 * Method: setSelected
 * Usage: chkbox.setSelected(state);
 * ---------------------------------
 * Sets the state of the check box.
 */

   void setSelected(bool state);

/*
 * Method: isSelected
 * Usage: if (chkbox.isSelected()) . . .
 * -------------------------------------
 * Returns <code>true</code> if the check box is selected.
 */

   bool isSelected();

/* Prototypes for the virtual methods */

   virtual std::string getType() const;
   virtual std::string toString() const;

private:
   std::string label;

};

/*
 * Class: GSlider
 * --------------
 * This class represents an onscreen slider.
 */

class GSlider : public GInteractor {

public:

/*
 * Constructor: GSlider
 * Usage: GSlider slider();
 *        GSlider slider(min, max, value);
 * ---------------------------------------
 * Creates a horizontal <code>GSlider</code>.  The second form allows
 * the client to specify the minimum value, maximum value, and current
 * value of the slider.  The first form is equivalent to calling
 * <code>GSlider(0, 100, 50)</code>.  Assigning an action command
 * to the slider causes the slider to generate an action event whenever
 * the slider value changes.
 */

   GSlider();
   GSlider(int min, int max, int value);

/*
 * Method: setValue
 * Usage: slider.setValue(value);
 * ------------------------------
 * Sets the current value of the slider.
 */

   void setValue(int value);

/*
 * Method: getValue
 * Usage: int value = slider.getValue();
 * -------------------------------------
 * Returns the current value of the slider.
 */

   int getValue();

/* Prototypes for the virtual methods */

   virtual std::string getType() const;
   virtual std::string toString() const;

private:
   void create(int min, int max, int value);
   int min;
   int max;

};

/*
 * Class: GTextField
 * -----------------
 * This class represents a text field.
 */

class GTextField : public GInteractor {

public:

/*
 * Constructor: GTextField
 * Usage: GTextField field();
 *        GTextField field(nChars);
 * --------------------------------
 * Creates a text field capable of holding <code>nChars</code> characters,
 * which defaults to 10.  Assigning an action command to the text field
 * causes it to generate an action event whenever the user types the
 * ENTER key.
 */

   GTextField();
   GTextField(int nChars);

/*
 * Method: setText
 * Usage: field.setText(str);
 * --------------------------
 * Sets the text of the field to the specified string.
 */

   void setText(std::string str);

/*
 * Method: getText
 * Usage: string str = field.getText();
 * ------------------------------------
 * Returns the contents of the text field.
 */

   std::string getText();

/* Prototypes for the virtual methods */

   virtual std::string getType() const;
   virtual std::string toString() const;

};

/*
 * Class: GChooser
 * ---------------
 * This class represents a selectable list.
 */

class GChooser : public GInteractor {

public:

/*
 * Constructor: GChooser
 * Usage: GChooser chooser();
 * --------------------------
 * Creates a chooser that initially contains no items, which are added
 * using the <code>addItem</code> method.  Assigning an action command
 * to the chooser causes it to generate an action event whenever the
 * user selects an item.
 */

   GChooser();

/*
 * Method: addItem
 * Usage: chooser.addItem(item);
 * -----------------------------
 * Adds a new item consisting of the specified string.
 */

   void addItem(std::string item);

/*
 * Method: setSelectedItem
 * Usage: chooser.setSelectedItem(item);
 * -------------------------------------
 * Sets the chooser so that it shows the specified item.  If the item
 * does not exist in the chooser, no change occurs.
 */

   void setSelectedItem(std::string item);

/*
 * Method: getSelectedItem
 * Usage: string item = chooser.getSelectedItem();
 * -----------------------------------------------
 * Returns the current item selected in the chooser.
 */

   std::string getSelectedItem();

/* Prototypes for the virtual methods */

   virtual std::string getType() const;
   virtual std::string toString() const;

};

#endif
