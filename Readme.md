﻿### The Problem

Consider the following:

```javascript
App.prototype.init = function() {
	var exampleView = new ExampleView($('.js-example'));
}
```

When our app starts we find an arbitrary dom element (or elements) using 
a *css class* name js-example and use that to create an instance of our ExampleView class.

```javascript
ExampleView.prototype.createChildren = function() {
	this.$card = this.$element.find('.js-card');
	return this;
};
```

We find children using the *css class* name js-card.

```javascript
ExampleView.prototype.enable = function() {
	this.$card.on('click', this.onClickHandler)        
	this.$card.addClass('flipped');
};
```

Then we add **behaviour** to those dom elements using 
jquery | zepto | *that other framework* to bind a function
to our browser's implementation of the normalized 'click' event.

```javascript
ExampleView.prototype.onClick = function(e) {
	this.$card.toggleClass('flipped');
};
```

###What makes this a problem?

Our code is now directly / functionally dependent on our not only our html's structure, 
but also the names we choose to use in css.  
Keep in mind css is something totally unrelated to behaviour:

>"a style sheet language used for describing the presentation semantics (the look and formatting) of a document written in a markup language"
 [Wikipedia - CSS](http://en.wikipedia.org/wiki/Cascading_Style_Sheets)

Our html is separate from this logic intentionally.  Because we want to keep our 
views logic less and lightweight.  The biggest problem with this: *it is not apparent
to any machine or person at first glance or after uninformed inspection that js-example
is related to ExampleView 1:1 and js-card is related to it's children*. 

Furthermore:

+ traversing the dom tree by the attributes of its nodes is costly; we are required though, 
  to do it to add behaviour
+ our html is brittle, its structure is completely coupled if we intend to have functional behaviour
+ our markup is intentionally less semantic

### A long time ago, in a land...

In 2002 the idea of unobtrusive javascript was [conceived](http://www.kryogenix.org/code/browser/aqlists/).   
Internet Explorer 6 was on its way becoming the most widely used browser.  It followed little standards 
and is likely one of the worst web browsers in the short history of the internet.  This idea of 
unobtrusiveness was developed to mitigate its lack of adherence to standards.  

The [seven identified principles](http://en.wikipedia.org/wiki/Unobtrusive_JavaScript) of unobtrusive javascript:

>	1. Do not make any assumptions: Defensive programming techniques should allow for the possibilities that JavaScript may not run, 
>	  the browser may not support expected methods, the HTML may have changed, unexpected input devices may be in use and other scripts 
>	  may either not be present or may be encroaching on the global namespace.
>	2. Find your hooks and relationships, such as IDs and other aspects of the expected HTML.
>	3. Leave traversing individual DOM objects to the experts, such as to the CSS handler built into the browser where possible.
>	4. Understand browsers and users, particularly how they fail, what assumptions they make, and unusual configurations or usages.
>	5. Understand events, including how they 'bubble' and the features of the Event object that is passed to most event handlers.
>	6. Play well with other scripts by avoiding global function and variable names. 
>	7. Work for the next developer by using self-explanatory variable and function names, creating logical and readable code, 
>	  making dependencies obvious, and commenting any code that still might confuse.

### The Internet Is Evolving

The seven principles defined in 2007 no longer apply.  The web was a much different place and we were writing web pages as 
parts of a larger web application, tracking state on a server, the now defunct Windows Mobile was our idea of a smartphone, 
and wap was a relevant term.  The web has changed vastly.  Apple created the iPhone and Google (and its contributors) created Android.  
A few people bought a Windows Phone - which is by no means a similar operating system to its ancestor.  IE6 is finally almost dead, 
7 is dying, Microsoft has started an open source initiative (the only thing that remains unchanged is the existence of 
Apple's "Walled Garden"; and shame on them for that).  Most importantly we are writing web *applications* in one page.  
Business logic is sometimes written exlusively in javascript.  Noone uses type attributes on script tags because no 
other script language is relevant and thus its not required.  Our smartphones outpower the machines we used in 2007 
at one tenth the size.  Etc.  

#### Enough about that; about those seven principles:

>	+ Do not make any assumptions: Defensive programming techniques should allow for the possibilities that JavaScript may not run, 
>	  the browser may not support expected methods, the HTML may have changed, unexpected input devices may be in use and other scripts 
>	  may either not be present or may be encroaching on the global namespace.

Javascript not running is no longer relevant.  If it doesn't run we may not have a single page let alone a functional web application.
The HTML may have changed.  If we are looking for ids, classes, traversing the DOM - pretty much if we have written any js and the HTML 
changes (especially unexpectedly) said js is going to have to change with it.  Tiny code goblins shouldn't be messing around on github.
Unexpected input devices may be in use.  This is a fundamental shift and brings us (back) to a very important concept: we no longer 
write code to support browser differences and likewise hardware differences.  It is the job of the device and its web browser to 
translate handwriting, speech, keyboard layouts, screen metrics.

>	+ Find your hooks and relationships, such as IDs and other aspects of the expected HTML.
>	+ Leave traversing individual DOM objects to the experts, such as to the CSS handler built into the browser where possible.

Traverse and be merry.  Thou [hast plenty of unused cycles and battery cells](http://en.wikipedia.org/wiki/Sarcasm).  Remember to 
fully discharge your batteries between charges.  Especially the Lithium ion variety (don't really it will damage them).

>	+ Understand browsers and users, particularly how they fail, what assumptions they make, and unusual configurations or usages.

This should be revised for responsiveness and accessiblity.  We should no longer interpret this as perhaps the user has disabled 
javascript.  We can add something about whether they have connectivity and / or a gpu with nothing to do.

>	+ Understand events, including how they 'bubble' and the features of the Event object that is passed to most event handlers.

Please don't focus on plumbing code.  The inner workings of events should be the least of your worries.  Basic understanding is still required.

>	+ Play well with other scripts by avoiding global function and variable names. 

Has anyone outside of [Unity3D](http://unity3d.com) intentionally written code in a global scope for production?  Shame on you.  This still applies.

>	+ Work for the next developer by using self-explanatory variable and function names, creating logical and readable code, 
>	  making dependencies obvious, and commenting any code that still might confuse.

This most definitely still applies.  But it should be noted that 

```javascript
var exampleView = new ExampleView($('.js-example'));
```
means and explains nothing.  It is also only readable in the context of the document(s) that use it.  Without type safety, compilation, and completely 
separated - exactly what dependency is obvious to someone working on the document?  It is also not possible to understand the structural dependencies
that most definitely exist without fully understanding the behaviour.

-------

#### HTML and Javascript Are Lonely

Have you ever written testable, readable, separated code in any other language - in this manner?  Probably (hopefully) not.  
To illustrate this, I've put a few examples together (not exactly the same implementation, but the concepts outlined remain):

#### WPF: Xaml and C#

[MainWindow.xaml](http://github.com/bradgearon/cohesive/blob/master/examples/xaml/MainWindow.xaml)

```xml 
<Window x:Class="SeparationOfConcerns.MainWindow"
        xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
        xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
		>
  <Grid Name="exampleGrid">
    <Grid.ColumnDefinitions>
      <ColumnDefinition />
      <ColumnDefinition />
      <ColumnDefinition />
    </Grid.ColumnDefinitions>
    <Rectangle Style="{StaticResource Card}" Grid.Column="0" />
    <Rectangle Style="{StaticResource Card}" Grid.Column="1" />
    <Rectangle Style="{StaticResource Card}" Grid.Column="2" />
  </Grid>
</Window>
```

[MainWindow.xaml.cs](http://github.com/bradgearon/cohesive/blob/master/examples/xaml/MainWindow.xaml.cs)

```cs
using System.Windows;
using System.Windows.Media;
using System.Windows.Shapes;
namespace SeparationOfConcerns
{
  public partial class MainWindow : Window
  {
    public MainWindow()
    {
      InitializeComponent();
      Init();
    }

    public void Init()
    {
      var cardStyle = App.Current.Resources["Card"] as Style;
      var flippedStyle = App.Current.Resources["Flipped"] as Style;

      var children = VisualTreeHelper.GetChildrenCount(exampleGrid);

      for (var i = 0; i < children; i++)
      {
        var child = VisualTreeHelper.GetChild(exampleGrid, i) as Rectangle;

        if (child != null && cardStyle != null && child.Style == cardStyle)
        {
          child.MouseLeave += (o, args) => child.Style = cardStyle;
          child.MouseEnter += (o, args) => child.Style = flippedStyle;
        }
      }

    }
  }
}
```

This violates nearly every rule in the book for WPF applications.  It makes no sense.  Rebuttals welcome.

#### Android: XML and Java

[main.xml](http://github.com/bradgearon/cohesive/blob/master/examples/android/res/layout/main.xml)

```xml 
<?xml version="1.0" encoding="utf-8"?>
<LinearLayout
        xmlns:android="http://schemas.android.com/apk/res/android"
        android:layout_width="fill_parent"
        android:layout_margin="20dp"
        android:layout_height="fill_parent"
        android:id="@id/mainLayout">
        <com.example.cohesive_android.StyledView style="@style/Card"/>
        <com.example.cohesive_android.StyledView style="@style/Card"/>
        <com.example.cohesive_android.StyledView style="@style/Card"/>
</LinearLayout>
```

StyledView extends android.view and exposes the style attribute originally declared.

[Cohesive.java](http://github.com/bradgearon/cohesive/blob/master/examples/android/src/com/example/cohesive_android/Cohesive.java)

```java
package com.example.cohesive_android;

// imports left out for brevity
public class Cohesive extends Activity {
@Override
public void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.main);

    Resources themeWrapper = getResources();

    final int flippedColor = themeWrapper.getColor(R.color.Flipped);
    final int cardColor = themeWrapper.getColor(R.color.Card);

    LinearLayout ll = (LinearLayout) findViewById(R.id.mainLayout);
    int children = ll.getChildCount();

    for (int i = 0; i < children; i++) {
        View view = ll.getChildAt(i);
        if (view instanceof StyledView) {
            view.setOnTouchListener(new View.OnTouchListener() {
                @Override
                public boolean onTouch(View view, android.view.MotionEvent motionEvent) {
                    Drawable background = view.getBackground();
                    int color = 0;
                    if (background instanceof ColorDrawable)
                        color = ((ColorDrawable) background).getColor();
                    view.setBackgroundColor(color == cardColor ? flippedColor : cardColor);
                    return false;
                }
            });
        }
    }
	}
}
```

Side note: CSharp is much more concise... 
Anonymous delegates, var, and lambda FTW  (the latter is [coming in Java 8](http://docs.oracle.com/javase/tutorial/java/javaOO/lambdaexpressions.html)). 

Android's view out of the box won't let you have these wretched cross layer dependencies.

#### Qt: QML and C++

[main.xml](http://github.com/bradgearon/cohesive/blob/master/examples/qt/cohesive/mainwindow.ui)

```xml 
<?xml version="1.0" encoding="utf-8"?>
<ui version="4.0">
  <class>MainWindow</class>
  <widget class="QMainWindow" name="MainWindow">
    <widget class="QWidget" name="centralWidget">
      <widget class="HoverPushButton" name="pushbutton">
	    <property name="className" stdset="0">
		  <string>Card</string>
		</property>
	  </widget>
	</widget>
  </widget>
</ui>
```

Note only the important markup is included for brevity.

[mainwindow.cpp](http://github.com/bradgearon/cohesive/blob/master/examples/qt/cohesive/mainwindow.cpp)

```cpp
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObjectList children = ui->centralWidget->children();
    int childCount = children.count();

    foreach(QObject* child, children) {
        QVariant className = child->property("className");
        if(className == "Card") {
            connect(child, SIGNAL(onHover(QEvent*, bool, QObject*)), 
				this, SLOT(OnCardHover(QEvent*, bool, QObject*)));
        }
    }
}

void MainWindow::OnCardHover(QEvent *event, bool hover, QObject* sender) {
    QPushButton* b = (QPushButton*) sender;
    b->setProperty("className", hover ? "Flipped" : "Card");
    this->setStyleSheet(this->styleSheet());
}

MainWindow::~MainWindow()
{
    delete ui;
}
```

[mainwindow.h](http://github.com/bradgearon/cohesive/blob/master/examples/qt/cohesive/mainwindow.h)

```cpp
public slots:
    void OnCardHover(QEvent *event, bool hover, QObject* sender);
};
```

The slot exposed for the hover event.

[hoverpushbutton.h](http://github.com/bradgearon/cohesive/blob/master/examples/qt/cohesive/hoverpushbutton.h)

```cpp
private:
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
signals:
    void onHover(QEvent *event, bool hover, QObject* sender);
```

Override the enter/leave Event functions.  Defines a signal for the main window to connect to (basically an event handler for those unfamiliar with signals/slots).

[hoverpushbutton.cpp](http://github.com/bradgearon/cohesive/blob/master/examples/qt/cohesive/hoverpushbutton.cpp)

```cpp
void HoverPushButton::enterEvent(QEvent *event) {
    emit onHover(event, true, this);
}

void HoverPushButton::leaveEvent(QEvent *event) {
    emit onHover(event, false, this);
}
```

Implementation simply emits the signal with true or false based on hover...  
Normally one would use psuedo tracking states in the qt stylesheet (to change the style) or simply use the HoverPushButton class if that behavior was supossed to be implemented.
The latter could be thought of as similar to a directive (in Angular).  Something I'll cover more later.

---------

Why would we break a bunch of our own rules for the web, but not for any other language or ui framework?  
Perhaps its the exponentially more difficult (standards) [upgrade process](http://www.ie6countdown.com/).  
Perhaps its because the browser is a choice more so than your choice operating system's ui framework.
Likely its a combination of those and attempts to commercialize and (naturally) differentiate the browser -
that spawned from the (ridiculous) idea that one browser could render documents better than the rest; that
this platform built for collaboration could be corrupted and made proprietary by deliberately ignoring 
accepted standards and thus be used as a tool to promote [other products](http://windows.microsoft.com).
Thankfully thats no longer an issue.

Is it still necessary, then, to use so called "defensive programming techniques"?  Must an application written for the
web pretend it isn't just some client code running inside of another ui framework?  Does that application need to 
function with or without its interpreter?

### Modern Web Applications

So yes, [we used to write things like](https://news.ycombinator.com/item?id=5526058)

```html
<a href=”#” onclick=”doSomething()”>
```

But, everything broke because of commercialism and bad decisions.   So we bent the rules for the web, until we could 
overcome the bad decisions and came up with the antipattern that is unobtrusive javascript.  Every other ui framework
realized since then that declaritive markup is a good thing.  

Thus, now that we can - its definitely time to [move on](http://www.localytics.com/blog/2013/angularjs-at-localytics/).

#### Paradigm Shift;  DOM Elements Inherently have Behaviour (even more in HTML5)

Soon

















