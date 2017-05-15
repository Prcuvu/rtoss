var ToolMan={events:function(){if(!ToolMan._eventsFactory)throw"ToolMan Events module isn't loaded";return ToolMan._eventsFactory},css:function(){if(!ToolMan._cssFactory)throw"ToolMan CSS module isn't loaded";return ToolMan._cssFactory},coordinates:function(){if(!ToolMan._coordinatesFactory)throw"ToolMan Coordinates module isn't loaded";return ToolMan._coordinatesFactory},drag:function(){if(!ToolMan._dragFactory)throw"ToolMan Drag module isn't loaded";return ToolMan._dragFactory},dragsort:function(){if(!ToolMan._dragsortFactory)throw"ToolMan DragSort module isn't loaded";
return ToolMan._dragsortFactory},helpers:function(){return ToolMan._helpers},cookies:function(){if(!ToolMan._cookieOven)throw"ToolMan Cookie module isn't loaded";return ToolMan._cookieOven},junkdrawer:function(){return ToolMan._junkdrawer}};
ToolMan._helpers={map:function(a,b){for(var c=0,d=a.length;c<d;c++)b(a[c])},nextItem:function(a,b){if(a!=null){for(a=a.nextSibling;a!=null;){if(a.nodeName==b)return a;a=a.nextSibling}return null}},previousItem:function(a,b){for(a=a.previousSibling;a!=null;){if(a.nodeName==b)return a;a=a.previousSibling}return null},moveBefore:function(a,b){var c=a.parentNode;c.removeChild(a);c.insertBefore(a,b)},moveAfter:function(a,b){var c=a.parentNode;c.removeChild(a);c.insertBefore(a,b?b.nextSibling:null)}};
ToolMan._junkdrawer={serializeList:function(a){a=a.getElementsByTagName("li");for(var b=[],c=0,d=a.length;c<d;c++){var e=a[c];b.push(ToolMan.junkdrawer()._identifier(e))}return b.join("|")},inspectListOrder:function(a){alert(ToolMan.junkdrawer().serializeList(document.getElementById(a)))},restoreListOrder:function(a){var b=document.getElementById(a);if(b!=null)if(a=ToolMan.cookies().get("list-"+a)){a=a.split("|");for(var c=ToolMan.junkdrawer()._itemsByID(b),d=0,e=a.length;d<e;d++){var f=a[d];if(f in
c){f=c[f];b.removeChild(f);b.insertBefore(f,null)}}}},_identifier:function(a){var b=ToolMan.junkdrawer().trim,c;c=b(a.getAttribute("id"));if(c!=null&&c.length>0)return c;c=b(a.getAttribute("itemID"));if(c!=null&&c.length>0)return c;return b(a.innerHTML)},_itemsByID:function(a){var b=[];a=a.getElementsByTagName("li");for(var c=0,d=a.length;c<d;c++){var e=a[c];b[ToolMan.junkdrawer()._identifier(e)]=e}return b},trim:function(a){if(a==null)return null;return a.replace(/^(\s+)?(.*\S)(\s+)?$/,"$2")}};ToolMan._cookieOven={set:function(a,b,c){if(c){var d=new Date;d.setTime(d.getTime()+c*24*60*60*1E3);c="; expires="+d.toGMTString()}else c="";document.cookie=a+"="+b+c+"; path=/"},get:function(a){a=a+"=";for(var b=document.cookie.split(";"),c=0,d=b.length;c<d;c++){for(var e=b[c];e.charAt(0)==" ";)e=e.substring(1,e.length);if(e.indexOf(a)==0)return e.substring(a.length,e.length)}return null},eraseCookie:function(a){createCookie(a,"",-1)}};ToolMan._coordinatesFactory={create:function(a,b){return new _ToolManCoordinate(this,a,b)},origin:function(){return this.create(0,0)},topLeftPosition:function(a){var b=parseInt(ToolMan.css().readStyle(a,"left"));b=isNaN(b)?0:b;a=parseInt(ToolMan.css().readStyle(a,"top"));a=isNaN(a)?0:a;return this.create(b,a)},bottomRightPosition:function(a){return this.topLeftPosition(a).plus(this._size(a))},topLeftOffset:function(a){var b=this._offset(a);for(a=a.offsetParent;a;){b=b.plus(this._offset(a));a=a.offsetParent}return b},
bottomRightOffset:function(a){return this.topLeftOffset(a).plus(this.create(a.offsetWidth,a.offsetHeight))},scrollOffset:function(){return window.pageXOffset?this.create(window.pageXOffset,window.pageYOffset):document.documentElement?this.create(document.body.scrollLeft+document.documentElement.scrollLeft,document.body.scrollTop+document.documentElement.scrollTop):document.body.scrollLeft>=0?this.create(document.body.scrollLeft,document.body.scrollTop):this.create(0,0)},clientSize:function(){return window.innerHeight>=
0?this.create(window.innerWidth,window.innerHeight):document.documentElement?this.create(document.documentElement.clientWidth,document.documentElement.clientHeight):document.body.clientHeight>=0?this.create(document.body.clientWidth,document.body.clientHeight):this.create(0,0)},mousePosition:function(a){a=ToolMan.events().fix(a);return this.create(a.clientX,a.clientY)},mouseOffset:function(a){a=ToolMan.events().fix(a);if(a.pageX>=0||a.pageX<0)return this.create(a.pageX,a.pageY);else if(a.clientX>=
0||a.clientX<0)return this.mousePosition(a).plus(this.scrollOffset())},_size:function(a){return this.create(a.offsetWidth,a.offsetHeight)},_offset:function(a){return this.create(a.offsetLeft,a.offsetTop)}};function _ToolManCoordinate(a,b,c){this.factory=a;this.x=isNaN(b)?0:b;this.y=isNaN(c)?0:c}
_ToolManCoordinate.prototype={toString:function(){return"("+this.x+","+this.y+")"},plus:function(a){return this.factory.create(this.x+a.x,this.y+a.y)},minus:function(a){return this.factory.create(this.x-a.x,this.y-a.y)},min:function(a){return this.factory.create(Math.min(this.x,a.x),Math.min(this.y,a.y))},max:function(a){return this.factory.create(Math.max(this.x,a.x),Math.max(this.y,a.y))},constrainTo:function(a,b){var c=a.min(b);a=a.max(b);return this.max(c).min(a)},distance:function(a){return Math.sqrt(Math.pow(this.x-
a.x,2)+Math.pow(this.y-a.y,2))},reposition:function(a){a.style.top=this.y+"px";a.style.left=this.x+"px"}};ToolMan._cssFactory={readStyle:function(a,b){return a.style[b]?a.style[b]:a.currentStyle?a.currentStyle[b]:document.defaultView&&document.defaultView.getComputedStyle?document.defaultView.getComputedStyle(a,null).getPropertyValue(b):null}};ToolMan._dragFactory={createSimpleGroup:function(a,b){b=b?b:a;a=this.createGroup(a);a.setHandle(b);a.transparentDrag();a.onTopWhileDragging();return a},createGroup:function(a){var b=new _ToolManDragGroup(this,a),c=ToolMan.css().readStyle(a,"position");if(c=="static")a.style.position="relative";else c=="absolute"&&ToolMan.coordinates().topLeftOffset(a).reposition(a);b.register("draginit",this._showDragEventStatus);b.register("dragmove",this._showDragEventStatus);b.register("dragend",this._showDragEventStatus);
return b},_showDragEventStatus:function(){},constraints:function(){return this._constraintFactory},_createEvent:function(a,b,c){return new _ToolManDragEvent(a,b,c)}};function _ToolManDragGroup(a,b){this.factory=a;this.element=b;this._handle=null;this._thresholdDistance=0;this._transforms=[];this._listeners=[];this._listeners.draginit=[];this._listeners.dragstart=[];this._listeners.dragmove=[];this._listeners.dragend=[]}
_ToolManDragGroup.prototype={setHandle:function(a){var b=ToolMan.events();a.toolManDragGroup=this;b.register(a,"mousedown",this._dragInit);a.onmousedown=function(){return false};this.element!=a&&b.unregister(this.element,"mousedown",this._dragInit)},register:function(a,b){this._listeners[a].push(b)},addTransform:function(a){this._transforms.push(a)},verticalOnly:function(){this.addTransform(this.factory.constraints().vertical())},horizontalOnly:function(){this.addTransform(this.factory.constraints().horizontal())},
setThreshold:function(a){this._thresholdDistance=a},transparentDrag:function(a){a=typeof a!="undefined"?a:0.75;var b=ToolMan.css().readStyle(this.element,"opacity");this.register("dragstart",function(c){c=c.group.element;c.style.opacity=a;c.style.filter="alpha(opacity="+a*100+")"});this.register("dragend",function(c){c=c.group.element;c.style.opacity=b;c.style.filter="alpha(opacity=100)"})},onTopWhileDragging:function(a){a=typeof a!="undefined"?a:1E5;var b=ToolMan.css().readStyle(this.element,"z-index");
this.register("dragstart",function(c){c.group.element.style.zIndex=a});this.register("dragend",function(c){c.group.element.style.zIndex=b})},_dragInit:function(a){a=ToolMan.events().fix(a);var b=document.toolManDragGroup=this.toolManDragGroup;a=b.factory._createEvent("draginit",a,b);b._isThresholdExceeded=false;b._initialMouseOffset=a.mouseOffset;b._grabOffset=a.mouseOffset.minus(a.topLeftOffset);ToolMan.events().register(document,"mousemove",b._drag);document.onmousemove=function(){return false};
ToolMan.events().register(document,"mouseup",b._dragEnd);b._notifyListeners(a)},_drag:function(a){a=ToolMan.events().fix(a);var b=ToolMan.coordinates(),c=this.toolManDragGroup;if(c){var d=c.factory._createEvent("dragmove",a,c),e=d.mouseOffset.minus(c._grabOffset);if(!c._isThresholdExceeded){if(d.mouseOffset.distance(c._initialMouseOffset)<c._thresholdDistance)return;c._isThresholdExceeded=true;c._notifyListeners(c.factory._createEvent("dragstart",a,c))}for(i in c._transforms)e=c._transforms[i](e,
d);a=e.minus(d.topLeftOffset);d.topLeftPosition.plus(a).reposition(c.element);d.transformedMouseOffset=e.plus(c._grabOffset);c._notifyListeners(d);d=e.minus(b.topLeftOffset(c.element));if(d.x!=0||d.y!=0)b.topLeftPosition(c.element).plus(d).reposition(c.element)}},_dragEnd:function(a){a=ToolMan.events().fix(a);var b=this.toolManDragGroup;a=b.factory._createEvent("dragend",a,b);b._notifyListeners(a);this.toolManDragGroup=null;ToolMan.events().unregister(document,"mousemove",b._drag);document.onmousemove=
null;ToolMan.events().unregister(document,"mouseup",b._dragEnd)},_notifyListeners:function(a){var b=this._listeners[a.type];for(i in b)b[i](a)}};function _ToolManDragEvent(a,b,c){this.type=a;this.group=c;this.mousePosition=ToolMan.coordinates().mousePosition(b);this.transformedMouseOffset=this.mouseOffset=ToolMan.coordinates().mouseOffset(b);this.topLeftPosition=ToolMan.coordinates().topLeftPosition(c.element);this.topLeftOffset=ToolMan.coordinates().topLeftOffset(c.element)}
_ToolManDragEvent.prototype={toString:function(){return"mouse: "+this.mousePosition+this.mouseOffset+"    xmouse: "+this.transformedMouseOffset+"    left,top: "+this.topLeftPosition+this.topLeftOffset}};ToolMan._dragFactory._constraintFactory={vertical:function(){return function(a,b){b=b.topLeftOffset.x;return a.x!=b?a.factory.create(b,a.y):a}},horizontal:function(){return function(a,b){b=b.topLeftOffset.y;return a.y!=b?a.factory.create(a.x,b):a}}};ToolMan._dragsortFactory={makeSortable:function(a){a=ToolMan.drag().createSimpleGroup(a);a.register("dragstart",this._onDragStart);a.register("dragmove",this._onDragMove);a.register("dragend",this._onDragEnd);return a},makeListSortable:function(a){var b=ToolMan.helpers(),c=ToolMan.coordinates(),d=a.getElementsByTagName("li");b.map(d,function(g){g=dragsort.makeSortable(g);g.setThreshold(4);var j,k;g.addTransform(function(h){return h.constrainTo(j,k)});g.register("dragstart",function(){var h=a.getElementsByTagName("li");
j=k=c.topLeftOffset(h[0]);for(var l=1,n=h.length;l<n;l++){var m=c.topLeftOffset(h[l]);j=j.min(m);k=k.max(m)}})});for(var e=1,f=arguments.length;e<f;e++)b.map(d,arguments[e])},_onDragStart:function(){},_onDragMove:function(a){var b=ToolMan.helpers(),c=ToolMan.coordinates(),d=a.group.element;a=a.transformedMouseOffset;for(var e=null,f=b.previousItem(d,d.nodeName);f!=null;){var g=c.bottomRightOffset(f);if(a.y<=g.y&&a.x<=g.x)e=f;f=b.previousItem(f,d.nodeName)}if(e!=null)b.moveBefore(d,e);else{for(f=b.nextItem(d,
d.nodeName);f!=null;){g=c.topLeftOffset(f);if(g.y<=a.y&&g.x<=a.x)e=f;f=b.nextItem(f,d.nodeName)}e!=null&&b.moveBefore(d,b.nextItem(e,d.nodeName))}},_onDragEnd:function(a){ToolMan.coordinates().create(0,0).reposition(a.group.element)}};ToolMan._eventsFactory={fix:function(a){if(!a)a=window.event;if(a.target){if(a.target.nodeType==3)a.target=a.target.parentNode}else if(a.srcElement)a.target=a.srcElement;return a},register:function(a,b,c){if(a.addEventListener)a.addEventListener(b,c,false);else if(a.attachEvent){if(!a._listeners)a._listeners=[];a._listeners[b]||(a._listeners[b]=[]);var d=function(){c.apply(a,[])};a._listeners[b][c]=d;a.attachEvent("on"+b,d)}},unregister:function(a,b,c){if(a.removeEventListener)a.removeEventListener(b,
c,false);else a.detachEvent&&a._listeners&&a._listeners[b]&&a._listeners[b][c]&&a.detachEvent("on"+b,a._listeners[b][c])}};