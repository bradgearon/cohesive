# DOM Element Behaviour
## Coupled or Cohesive

### The Problem

Consider the following:

	App.prototype.init = function() {
		var exampleView = new ExampleView($('.js-example'));
	}

...

	ExampleView.prototype.createChildren = function() {
		this.$card = this.$element.find('.js-card');
        
        return this;
	};

...

    ExampleView.prototype.enable = function() {

		this.$card
            .on('click', this.onClickHandler)        
        this.$card
            .addClass('flipped');
        
...

    ExampleView.prototype.onClick = function(e) {
        this.$card.toggleClass('flipped');
    };

When our app starts we create a backbone collection, then we find an arbitrary dom element (or elements) 
using a *css class* name js-example, and finding children of that element by *css class* name js-card.  Then 
we add **behaviour** to that element using jquery || zepto || *whatever that other framework is called* to
bind a function to the **browser's** implementation of click - normalized by our choice of framework.  Our backbone
collection is an extension of a predefined object our app will implement keeping specific requirements, rules, and 
behaviours in mind.  

Consider this alternative:


