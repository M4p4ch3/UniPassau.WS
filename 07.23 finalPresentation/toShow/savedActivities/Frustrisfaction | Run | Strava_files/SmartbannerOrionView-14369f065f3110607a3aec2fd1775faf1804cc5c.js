(function(){var t=function(t,n){function o(){this.constructor=t}for(var e in n)r.call(n,e)&&(t[e]=n[e]);return o.prototype=n.prototype,t.prototype=new o,t.__super__=n.prototype,t},r={}.hasOwnProperty;Strava.module("Strava.Ui.Views"),Strava.Ui.Views.SmartbannerOrionView=function(r){function n(){return n.__super__.constructor.apply(this,arguments)}return t(n,r),n.prototype.el="#smartbanner-orion",n.prototype.initialize=function(){var t;return t=this.$$("#global-header"),this.$el.affix({offset:{top:0}}).on("affixed.bs.affix",function(r){return function(){return t.css("margin-top",r.$el.outerHeight(!0))}}(this)).on("affixed-top.bs.affix",function(){return t.css("margin-top",0)})},n}(Backbone.View)}).call(this);