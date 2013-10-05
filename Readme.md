# DOM Element Behaviour
## Coupled or Cohesive

### The Problem

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

What makes this a problem:

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

### The obvious truth exposed

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

### HTML and js Are Lonely

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










