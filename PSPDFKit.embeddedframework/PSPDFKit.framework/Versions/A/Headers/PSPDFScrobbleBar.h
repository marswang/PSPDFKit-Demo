//
//  PSPDFScrobbleBar.h
//  PSPDFKit
//
//  Copyright 2011-2013 Peter Steinberger. All rights reserved.
//

#import "PSPDFKitGlobal.h"
#import "PSPDFCache.h"

@class PSPDFViewController;

///
/// PDF thumbnail scrobble bar - similar to iBooks.
///
@interface PSPDFScrobbleBar : UIView <PSPDFCacheDelegate>

/// PDF controller delegate. We use KVO, so no weak here.
/// Re-set pdfController to update the tintColor.
@property (nonatomic, unsafe_unretained) PSPDFViewController *pdfController;

/// Updates toolbar, re-aligns page screenshots. Registers in the runloop and works later.
- (void)updateToolbarAnimated:(BOOL)animated;

/// *Instantly* updates toolbar.
- (void)updateToolbarForced;

/// Updates the page marker. call manually after alpha > 0 !
- (void)updatePageMarker;

/// Current selected page.
@property (nonatomic, assign) NSUInteger page;

/// Access toolbar. It's in an own view, to have a transparent toolbar but non-transparent images.
/// Alpha is set to 0.7, can be changed.
@property (nonatomic, strong) UIToolbar *toolbar;

/// Left border margin. Defaults to thumbnailMargin. Set higher to allow custom buttons.
@property (nonatomic, assign) CGFloat leftBorderMargin;

/// Right border margin. Defaults to thumbnailMargin. Set higher to allow custom buttons.
@property (nonatomic, assign) CGFloat rightBorderMargin;

@end


@interface PSPDFScrobbleBar (SubclassingHooks)

// Returns YES if toolbar is in landscape/iPhone mode.
- (BOOL)isSmallToolbar;

// Returns toolbar height. (depending on isSmallToolbar)
- (CGFloat)scrobbleBarHeight;

// Returns size of the bottom thumbnails. (depending on isSmallToolbar)
- (CGSize)scrobbleBarThumbSize;

// Margin between thumbnails. Defaults to 2.
@property (nonatomic, assign) CGFloat thumbnailMargin;

// Size multiplier for the current page thumbnail. Defaults to 1.35.
@property (nonatomic, assign) CGFloat pageMarkerSizeMultiplier;

@end
