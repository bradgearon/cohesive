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

Consider this alternative:


