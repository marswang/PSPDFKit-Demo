//
//  PSPDFMagazine.h
//  PSPDFCatalog
//
//  Copyright 2011-2013 Peter Steinberger. All rights reserved.
//

@class PSCMagazineFolder;

///
/// Represents a magazine in the PSPDFKiosk example.
///
@interface PSCMagazine : PSPDFDocument

/// Initializes a magazine object with the specified path.
+ (PSCMagazine *)magazineWithPath:(NSString *)path;

/// Returns the coverImage, which is the first page of the magazine.
/// Here we download that from the web to have sth to show before the pdf is available.
- (UIImage *)coverImageForSize:(CGSize)size;

/// Magazine folder. Weak to break the retain cycle.
@property (nonatomic, weak) PSCMagazineFolder *folder; // weak!

/// URL for downloading the pdf.
@property (nonatomic, strong) NSURL *URL;

/// URL for downloading image.
@property (nonatomic, strong) NSURL *imageURL;

/// Handles serialization/deserialization of the last known viewState (page, ...)
@property (nonatomic, strong) PSPDFViewState *lastViewState;

/// YES if magazine is currently downloading.
@property (nonatomic, assign, getter=isDownloading) BOOL downloading;

/// YES if magazine is on-disk and/or successfully downloaded.
@property (nonatomic, assign, getter=isAvailable) BOOL available;

/// YES if the magazine can be deleted. NO if it's within the app bundle, which can't be edited.
@property (nonatomic, assign, getter=isDeletable, readonly) BOOL deletable;

@end
