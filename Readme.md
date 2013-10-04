# DOM Element Behaviour
## Coupled or Cohesive

### The Problem

Consider the following:

	App.prototype.init = function() {
		var exampleView = new ExampleView($('.js-example'));
	}

...

When our app starts we find an arbitrary dom element (or elements) using 
a *css class* name js-example and use that to create an instance of our ExampleView class.

	ExampleView.prototype.createChildren = function() {
		this.$card = this.$element.find('.js-card');
		return this;
	};

...

We find children using the *css class* name js-card.

    ExampleView.prototype.enable = function() {
		this.$card
            .on('click', this.onClickHandler)        
       this.$card
            .addClass('flipped');
	};

...

Then we add **behaviour** to those dom elements using 
jquery | zepto | *that other framework* to bind a function
to our browser's implementation of the normalized 'click' event.
	
    ExampleView.prototype.onClick = function(e) {
        this.$card.toggleClass('flipped');
    };

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

Its much too easy to forget the basis for our separation of concerns.  In 2002 the idea of unobtrusive 
javascript was [conceived](http://www.kryogenix.org/code/browser/aqlists/).   Internet Explorer 6 was 
on its way becoming the most widely used browser.  It followed little standards and is likely one of the
worst web browsers in the short history of the internet.  This idea of unobtrusiveness was developed to
mitigate its lack of adherence to standards.  The seven identified principles of 


