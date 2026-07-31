/****************************************************************************
 Copyright (c) 2010 cocos2d-x.org
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
 
#import "AppController.h"
#import "AppDelegate.h"

@implementation AppController

	static AppDelegate s_sharedApplication;

	@synthesize window, glView;

	-(void) applicationDidFinishLaunching:(NSNotification *)aNotification
	{
		// create the window
		// note that using NSResizableWindowMask causes the window to be a little
		// smaller and therefore ipad graphics are not loaded

		// Window scale over the 480x320 design resolution. 2 == same "2x" feel as the
		// win32 build (setFrameZoomFactor(2)); bump to 3.0 for an even bigger window.
		const CGFloat kWinScale = 2.0;
		NSRect rect = NSMakeRect(200, 200, 480 * kWinScale, 320 * kWinScale);
		window = [[NSWindow alloc] initWithContentRect:rect
			styleMask:( NSClosableWindowMask | NSTitledWindowMask )
			backing:NSBackingStoreBuffered
			defer:YES];

        NSOpenGLPixelFormatAttribute attributes[] = {
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFADepthSize, 24,
            NSOpenGLPFAStencilSize, 8,
            0
        };

        NSOpenGLPixelFormat *pixelFormat = [[[NSOpenGLPixelFormat alloc] initWithAttributes:attributes] autorelease];

		// allocate our GL view
		// (isn't there already a shared EAGLView?)
		glView = [[EAGLView alloc] initWithFrame:rect pixelFormat:pixelFormat];

		// Keep the GL drawable at 1 pixel-per-point (no Retina 2x backing). cocos2d-x 2.2.6
		// computes the GL viewport in POINTS; on a Retina screen the NSOpenGLView otherwise
		// gets a 2x-pixel drawable while the viewport stays 1x, so the scene only fills the
		// bottom-left quarter of the window. Forcing a 1x surface makes pixels == points, so
		// setViewPortInPoints() fills the whole window (menu AND battle).
		[glView setWantsBestResolutionOpenGLSurface:NO];

		// set window parameters
		[window becomeFirstResponder];
		[window setContentView:glView];
		[window setTitle:@"火影战记 NarutoSenki"];
		[window makeKeyAndOrderFront:self];
		[window setAcceptsMouseMovedEvents:NO];

		// Force the GL context current BEFORE run(). run() calls setOpenGLView ->
		// CCConfiguration::gatherGPUInfo(), which calls glGetString() synchronously.
		// prepareOpenGL (which makes the context current) is otherwise only invoked
		// lazily on the first draw, i.e. after this method returns — so without this
		// glGetString() returns NULL and std::string(NULL) aborts on modern macOS.
		[[glView openGLContext] makeCurrentContext];

		cocos2d::CCApplication::sharedApplication()->run();
	}

	-(BOOL) applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)theApplication
	{
		return YES;
	}

	-(void) dealloc
	{
		cocos2d::CCDirector::sharedDirector()->end();
		[super dealloc];
	}

#pragma mark -
#pragma mark IB Actions

	-(IBAction) toggleFullScreen:(id)sender
	{
		EAGLView* pView = [EAGLView sharedEGLView];
		[pView setFullScreen:!pView.isFullScreen];
	}

	-(IBAction) exitFullScreen:(id)sender
	{
		[[EAGLView sharedEGLView] setFullScreen:NO];
	}

@end
