/*
 * File: gevents.h
 * ---------------
 * This file defines the event types used in the StanfordCPPLib
 * graphics libraries.  The structure of this package is adapted from
 * the Java event model.
 */

#ifndef _gevents_h
#define _gevents_h

#include <string>
#include "gwindow.h"

/*
 * Type: EventClassType
 * --------------------
 * This enumeration type defines the event classes.
 */

enum EventClassType {
   NULL_EVENT,         /* Indicates an uninitialized event              */
   WINDOW_EVENT,       /* Indicates a window-system event               */
   ACTION_EVENT,       /* Indicates an event with an associated action  */
   TIMER_EVENT,        /* Indicates an interval timer event             */
   MOUSE_EVENT,        /* Indicates a mouse event                       */
   KEY_EVENT           /* Indicates an event generated by the keyboard  */
};

/*
 * Type: WindowEventType
 * ---------------------
 * This enumeration type defines the event types for window events.
 */

enum WindowEventType {
   WINDOW_CLOSED,      /* Generated when the window is closed           */
   WINDOW_RESIZED      /* Generated when the window is resized          */
};

/*
 * Type: ActionEventType
 * ---------------------
 * This enumeration type defines the event types for action events.
 */

enum ActionEventType {
   ACTION_PERFORMED    /* Generated when a user action is performed     */
};

/*
 * Type: MouseEventType
 * --------------------
 * This enumeration type defines the event types for mouse events.
 */

enum MouseEventType {
   MOUSE_PRESSED,      /* Generated when the mouse button is pressed     */
   MOUSE_RELEASED,     /* Generated when the mouse button is released    */
   MOUSE_CLICKED,      /* Generated on clicks after PRESSED and RELEASED */
   MOUSE_MOVED,        /* Generated when the mouse is moved              */
   MOUSE_DRAGGED       /* Generated on mouse motion with the button down */
};

/*
 * Type: KeyEventType
 * ------------------
 * This enumeration type defines the event types for keyboard events.
 */

enum KeyEventType {
   KEY_PRESSED,        /* Generated when a key is pressed                */
   KEY_RELEASED,       /* Generated when a key is released               */
   KEY_TYPED           /* Generated after PRESSED and RELEASED on a key  */
};

/*
 * Type: ModifierCodes
 * -------------------
 * This enumeration type defines a set of constants used to check whether
 * modifiers are in effect.
 */

enum ModifierCodes {
   SHIFT_DOWN     = 1 << 0,
   CTRL_DOWN      = 1 << 1,
   META_DOWN      = 1 << 2,
   ALT_DOWN       = 1 << 3,
   ALT_GRAPH_DOWN = 1 << 4,
   BUTTON1_DOWN   = 1 << 5,
   BUTTON2_DOWN   = 1 << 6,
   BUTTON3_DOWN   = 1 << 7
};

/*
 * Constants: Key codes
 * --------------------
 * These constants define the names of the key codes returned in a
 * key event.
 */

extern const int ESCAPE_KEY;
extern const int BACKSPACE_KEY;
extern const int DELETE_KEY;
extern const int TAB_KEY;
extern const int CLEAR_KEY;
extern const int ENTER_KEY;
extern const int UP_ARROW_KEY;
extern const int DOWN_ARROW_KEY;
extern const int LEFT_ARROW_KEY;
extern const int RIGHT_ARROW_KEY;
extern const int HELP_KEY;
extern const int HOME_KEY;
extern const int PAGE_UP_KEY;
extern const int PAGE_DOWN_KEY;
extern const int END_KEY;
extern const int F1_KEY;
extern const int F2_KEY;
extern const int F3_KEY;
extern const int F4_KEY;
extern const int F5_KEY;
extern const int F6_KEY;
extern const int F7_KEY;
extern const int F8_KEY;
extern const int F9_KEY;
extern const int F10_KEY;
extern const int F11_KEY;
extern const int F12_KEY;

/*
 * Type: TimerEventType
 * --------------------
 * This enumeration type defines the event types for timer events.
 */

enum TimerEventType {
   TIMER_TICKED        /* Generated when the interval timer ticks       */
};

/* Forward definitions */

class GWindowEvent;
class GActionEvent;
class GMouseEvent;
class GKeyEvent;
class GTimerEvent;
class GTimer;
class GObject;

/*
 * Class: GEvent
 * -------------
 * This class is the root of the hierarchy for all events.  The
 * primary purpose of this general class is as the parameter to
 * the <code>waitForEvent</code> and <code>getNextEvent</code>
 * functions.  Code that uses these functions to wait for events
 * of more than one class must typically cast the event to the
 * appropriate subclass.
 *
 * <p>The standard paradigm for using <code>GEvent</code> is illustrated
 * by the following program, which allows the user to draw lines on the
 * graphics window:
 *
 *<pre>
 *    int main() {
 *       GWindow gw;
 *       GLine *line;
 *       while (true) {
 *          GMouseEvent e;
 *          waitForEvent(e);
 *          if (e.getEventType() == MOUSE_PRESSED) {
 *             line = new GLine(e.getX(), e.getY(), e.getX(), e.getY());
 *             gw.add(line);
 *          } else if (e.getEventType() == MOUSE_DRAGGED) {
 *             line->setEndPoint(e.getX(), e.getY());
 *          }
 *       }
 *    }
 *</pre>
 */

class GEvent {

public:

/*
 * Constructor: GEvent
 * Usage: GEvent event;
 * --------------------
 * Ensures that an event is properly initialized to a <code>NULL</code>
 * event.
 */

   GEvent();

/*
 * Method: getEventClass
 * Usage: EventClassType eventClass = e.getEventClass();
 * -----------------------------------------------------
 * Returns the enumerated type constant indicating the class of the
 * event.
 */

   EventClassType getEventClass() const;

/*
 * Method: getEventTime
 * Usage: double time = e.getEventTime();
 * --------------------------------------
 * Returns the system time in milliseconds at which the event occurred.
 * To ensure portability among systems that represent time in different
 * ways, the StanfordCPPLib packages use type <code>double</code> to
 * represent time, which is always encoded as the number of milliseconds
 * that have elapsed since 00:00:00 UTC on January 1, 1970, which is
 * the conventional zero point for computer-based time systems.
 */

   double getEventTime() const;

/*
 * Method: getModifiers
 * Usage: int modifiers = e.getModifiers();
 * ----------------------------------------
 * Returns an integer whose bits indicate what modifiers are in effect.
 * To check whether the shift key is down, for example, one could use
 * the following code:
 *
 *<pre>
 *    if (e.getModifiers() & SHIFT_DOWN) . . .
 *</pre>
 */

   int getModifiers() const;

/*
 * Method: toString
 * Usage: string str = e.toString();
 * ---------------------------------
 * Converts the event to a human-readable representation of the event.
 */

   virtual std::string toString() const;

/*
 * Operator: bool
 * Usage: if (e) . . .
 * -------------------
 * Converts the event to a Boolean value which is <code>true</code> if the
 * event is valid.
 */

   operator bool() const;

/* Private section */

/**********************************************************************/
/* Note: Everything below this point in the file is logically part    */
/* of the implementation and should not be of interest to clients.    */
/**********************************************************************/

/*
 * Method: setEventTime
 * Usage: e.setEventTime(time);
 * ----------------------------
 * Sets the event time field for this event.  The event system needs
 * access to this method, but conventional clients don't.
 */

   void setEventTime(double time);

/*
 * Method: setModifiers
 * Usage: e.setModifiers(modifiers);
 * ---------------------------------
 * Sets the modifiers field for this event.  The event system needs
 * access to this method, but conventional clients don't.
 */

   void setModifiers(int modifiers);

private:

/*
 * Instance variables
 * ------------------
 * Implementation note: All the variables from the subclasses are included
 * in the outer class to make it possible to convert between general events
 * and the various subclasses.  By keeping all event classes the same size,
 * this design avoids any issues of slicing off parts of the data during
 * such conversions.
 */

/* General events */

   EventClassType eventClass;
   int eventType;
   int modifiers;
   double eventTime;
   bool isValid;
   std::string sourceKey;

/* Window, mouse, and key events */

   GWindow *gw;

/* Action events */

   GObject *source;
   std::string actionCommand;

/* Mouse events */

   double x;
   double y;

/* Key events */

   int keyChar;
   int keyCode;

/* Timer events */

   GTimer *timer;

/* Friend specifications */

friend class GWindowEvent;
friend class GActionEvent;
friend class GMouseEvent;
friend class GKeyEvent;
friend class GTimerEvent;

};

/*
 * Function: waitForEvent
 * Usage: waitForEvent(e);
 * -----------------------
 * Dismisses the process until an event occurs.  When it does, the
 * <code>waitForEvent</code> function returns with the details of
 * the event.  The parameter <code>e</code> can be either a general
 * <code>GEvent</code> variable or one of the specific subclasses.
 * In the former case, the function returns when any event occurs.
 * Clients should use this approach if they need to respond to more
 * than one class of event.  As an example, the following code is
 * the canonical event loop for an animated application that
 * needs to respond to mouse, key, and timer events:
 *
 *<pre>
 *    GTimer timer(ANIMATION_DELAY_IN_MILLISECONDS);
 *    timer.start();
 *    while (true) {
 *       GEvent e;
 *       waitForEvent(e);
 *       switch (e.getEventClass()) {
 *        case TIMER_EVENT:
 *          takeAnimationStep();
 *          break;
 *        case MOUSE_EVENT:
 *          handleMouseEvent(GMouseEvent(e));
 *          break;
 *        case KEY_EVENT:
 *          handleKeyEvent(GKeyEvent(e));
 *          break;
 *       }
 *    }
 *</pre>
 *
 * For applications that are interested only in mouse events,
 * for example, this code can be simplified as follows:
 *
 *<pre>
 *    while (true) {
 *       GMouseEvent e;
 *       waitForEvent(e);
 *       handleMouseEvent(e);
 *    }
 *</pre>
 */

void waitForEvent(GEvent & e);
void waitForEvent(GWindowEvent & e);
void waitForEvent(GActionEvent & e);
void waitForEvent(GMouseEvent & e);
void waitForEvent(GKeyEvent & e);
void waitForEvent(GTimerEvent & e);

/*
 * Function: waitForClick
 * Usage: waitForClick();
 *        waitForClick(e);
 *        waitForClick(mouseEvent);
 *        waitForClick(actionEvent);
 * ---------------------------------
 * Waits for a mouse click or action to occur anywhere in the window,
 * discarding any other events.  If the client passes an event as a
 * reference parameter, the function will fill in the details of the
 * triggering event.
 */

void waitForClick();
void waitForClick(GEvent & e);
void waitForClick(GMouseEvent & mouseEvent);
void waitForClick(GActionEvent & actionEvent);

/*
 * Function: getNextEvent
 * Usage: if (getNextEvent(e)) . . .
 * ---------------------------------
 * Checks to see if there are any events waiting on the event queue.
 * If so, <code>getNextEvent</code> fills in the structure of the event
 * with the first event in the queue and returns <code>true</code>.  If
 * there are no events, <code>getNextEvent</code> returns <code>false</code>.
 * As with <code>waitForEvent</code>, the parameter <code>e</code> can
 * be either a <code>GEvent</code> variable or one of the specific
 * subclasses.  Clients should use this form of the call if they
 * need to support animation in the main thread, as in the following
 * code example:
 *
 *<pre>
 *    while (true) {
 *       GEvent e;
 *       if (getNextEvent(e)) {
 *          switch (e.getEventClass()) {
 *           case MOUSE_EVENT:
 *             handleMouseEvent(GMouseEvent(e));
 *             break;
 *           case KEY_EVENT:
 *             handleKeyEvent(GKeyEvent(e));
 *             break;
 *          }
 *       } else {
 *          takeAnimationStep();
 *       }
 *    }
 *</pre>
 */

bool getNextEvent(GEvent & e);
bool getNextEvent(GWindowEvent & e);
bool getNextEvent(GActionEvent & e);
bool getNextEvent(GMouseEvent & e);
bool getNextEvent(GKeyEvent & e);
bool getNextEvent(GTimerEvent & e);

/*
 * Class: GWindowEvent
 * -------------------
 * This event subclass represents a window event.
 */

class GWindowEvent : public GEvent {

public:

/*
 * Constructor: GWindowEvent
 * Usage: GWindowEvent windowEvent;
 *        GWindowEvent windowEvent(e);
 *        GWindowEvent windowEvent(type, gw);
 * ------------------------------------------
 * Creates a <code>GWindowEvent</code> using the specified parameters or
 * those taken from the more general event <code>e</code>.
 */

   GWindowEvent();
   GWindowEvent(GEvent e);
   GWindowEvent(WindowEventType type, GWindow *gw);

/*
 * Method: getEventType
 * Usage: WindowEventType type = e.getEventType();
 * -----------------------------------------------
 * Returns the enumerated type constant corresponding to the specific
 * type of window event.
 */

   WindowEventType getEventType() const;

/*
 * Method: getGWindow
 * Usage: GWindow *gw = e.getGWindow();
 * ------------------------------------
 * Returns a pointer to the graphics window in which this event occurred.
 */

   GWindow *getGWindow() const;

/*
 * Method: toString
 * Usage: string str = e.toString();
 * ---------------------------------
 * Converts the event to a human-readable representation of the event.
 */

   std::string toString() const;

};

/*
 * Class: GActionEvent
 * -------------------
 * This event subclass represents an action event.
 */

class GActionEvent : public GEvent {

public:

/*
 * Constructor: GActionEvent
 * Usage: GActionEvent actionEvent;
 *        GActionEvent actionEvent(e);
 *        GActionEvent actionEvent(type, source, actionCommand);
 * -------------------------------------------------------------
 * Creates a <code>GActionEvent</code> using the specified parameters or
 * those taken from the more general event <code>e</code>.
 */

   GActionEvent();
   GActionEvent(GEvent e);
   GActionEvent(ActionEventType type, GObject *source,
                                      std::string actionCommand);

/*
 * Method: getEventType
 * Usage: ActionEventType type = e.getEventType();
 * -----------------------------------------------
 * Returns the enumerated type constant corresponding to the specific
 * type of action event.
 */

   ActionEventType getEventType() const;

/*
 * Method: getSource
 * Usage: GObject *gobj = e.getSource();
 * -------------------------------------
 * Returns a pointer to the <code>GObject</code> that generated this event.
 */

   GObject *getSource() const;

/*
 * Method: getActionCommand
 * Usage: string cmd = e.getActionCommand();
 * -----------------------------------------
 * Returns the action command associated with this event.
 */

   std::string getActionCommand() const;

/*
 * Method: toString
 * Usage: string str = e.toString();
 * ---------------------------------
 * Converts the event to a human-readable representation of the event.
 */

   std::string toString() const;

};

/*
 * Class: GMouseEvent
 * ------------------
 * This event subclass represents a mouse event.
 */

class GMouseEvent : public GEvent {

public:

/*
 * Constructor: GMouseEvent
 * Usage: GMouseEvent mouseEvent;
 *        GMouseEvent mouseEvent(e);
 *        GMouseEvent mouseEvent(type, gw, x, y);
 * ----------------------------------------------
 * Creates a <code>GMouseEvent</code> using the specified parameters or
 * those taken from the more general event <code>e</code>.
 */

   GMouseEvent();
   GMouseEvent(GEvent e);
   GMouseEvent(MouseEventType type, GWindow *gw, double x, double y);

/*
 * Method: getEventType
 * Usage: MouseEventType type = e.getEventType();
 * ----------------------------------------------
 * Returns the enumerated type constant corresponding to the specific
 * type of mouse event.
 */

   MouseEventType getEventType() const;

/*
 * Method: getGWindow
 * Usage: GWindow *gw = e.getGWindow();
 * ------------------------------------
 * Returns a pointer to the graphics window in which this event occurred.
 */

   GWindow *getGWindow() const;

/*
 * Method: getX
 * Usage: double x = getX();
 * -------------------------
 * Returns the <i>x</i> coordinate at which the event occurred relative
 * to the window origin at the upper left corner of the window.
 */

   double getX() const;

/*
 * Method: getY
 * Usage: double y = getY();
 * -------------------------
 * Returns the <i>y</i> coordinate at which the event occurred relative
 * to the window origin at the upper left corner of the window.
 */

   double getY() const;

/*
 * Method: toString
 * Usage: string str = e.toString();
 * ---------------------------------
 * Converts the event to a human-readable representation of the event.
 */

   std::string toString() const;

};

/*
 * Class: GKeyEvent
 * ----------------
 * This event subclass represents a key event.
 */

class GKeyEvent : public GEvent {

public:

/*
 * Constructor: GKeyEvent
 * Usage: GKeyEvent keyEvent;
 *        GKeyEvent keyEvent(e);
 *        GKeyEvent keyEvent(type, gw, ch, code);
 * ----------------------------------------------
 * Creates a <code>GKeyEvent</code> using the specified parameters or
 * those taken from the more general event <code>e</code>.
 */

   GKeyEvent();
   GKeyEvent(GEvent e);
   GKeyEvent(KeyEventType type, GWindow *gw, int keyChar, int keyCode);

/*
 * Method: getEventType
 * Usage: KeyEventType type = e.getEventType();
 * --------------------------------------------
 * Returns the enumerated type constant corresponding to the specific
 * type of key event.
 */

   KeyEventType getEventType() const;

/*
 * Method: getGWindow
 * Usage: GWindow *gw = e.getGWindow();
 * ------------------------------------
 * Returns a pointer to the graphics window in which this event occurred.
 */

   GWindow *getGWindow() const;

/*
 * Method: getKeyChar
 * Usage: char ch = e.getKeyChar();
 * --------------------------------
 * Returns the character represented by the keystroke, taking the modifier
 * keys into account.  For example, if the user types the <code>'a'</code>
 * key with the shift key down, <code>getKeyChar</code> will return
 * <code>'A'</code>.  If the key code in the event does not correspond
 * to a character, <code>getKeyChar</code> returns the null character.
 */

   char getKeyChar() const;

/*
 * Method: getKeyCode
 * Usage: int key = getKeyCode();
 * ------------------------------
 * Returns the integer code associated with the key in the event.
 */

   int getKeyCode() const;

/*
 * Method: toString
 * Usage: string str = e.toString();
 * ---------------------------------
 * Converts the event to a human-readable representation of the event.
 */

   std::string toString() const;

};

/*
 * Class: GTimerEvent
 * ------------------
 * This event subclass represents a timer event.
 */

class GTimerEvent : public GEvent {

public:

/*
 * Constructor: GTimerEvent
 * Usage: GTimerEvent timerEvent;
 *        GTimerEvent timerEvent(e);
 *        GTimerEvent timerEvent(type, tp);
 * ----------------------------------------
 * Creates a <code>GTimerEvent</code>.
 */

   GTimerEvent();
   GTimerEvent(GEvent e);
   GTimerEvent(TimerEventType type, GTimer *tp);

/*
 * Method: getEventType
 * Usage: TimerEventType type = e.getEventType();
 * ----------------------------------------------
 * Returns the enumerated type constant corresponding to the specific
 * type of timer event.
 */

   TimerEventType getEventType() const;

/*
 * Method: getGTimer
 * Usage: GTimer *tp = e.getGTimer();
 * ----------------------------------
 * Returns a pointer to the timer that generated this event.
 */

   GTimer *getGTimer() const;

/*
 * Method: toString
 * Usage: string str = e.toString();
 * ---------------------------------
 * Converts the event to a human-readable representation of the event.
 */

   std::string toString() const;

};

/*
 * Class: GTimer
 * -------------
 * This class implements a simple interval timer that generates a
 * <code>GTimerEvent</code> with a specified frequency.
 */

class GTimer {

public:

/*
 * Constructor: GTimer
 * Usage: GTimer timer(microseconds);
 * ----------------------------------
 * Creates a timer object that generates a <code>GTimerEvent</code>
 * each time the specified number of microseconds has elapsed.  No
 * events are generated until the client calls <code>start</code>
 * on the timer.
 */

   GTimer(double microseconds);

/*
 * Destructor: ~GTimer
 * -------------------
 * Frees the resources associated with the timer.
 */

   virtual ~GTimer();

/*
 * Method: start
 * Usage: timer.start();
 * ---------------------
 * Starts the timer.  A timer continues to generate timer events until it
 * is stopped; to achieve the effect of a one-shot timer, the simplest
 * approach is to call the <code>stop</code> method inside the event
 * handler.
 */

   void start();

/*
 * Method: stop
 * Usage: timer.stop();
 * --------------------
 * Stops the timer so that it stops generating events until it is restarted.
 */

   void stop();

/* Private section */

private:

/* Instance variables */

   std::string id;

};

GTimer *getGTimer(std::string id);

#endif
