//
//  PSPDFFileAnnotationProvider.h
//  PSPDFKit
//
//  Copyright (c) 2012 Peter Steinberger. All rights reserved.
//

#import "PSPDFKitGlobal.h"
#import "PSPDFAnnotationProvider.h"

@class PSPDFLinkAnnotation;

/**
 Concrete implementation of the PSPDFAnnotationProvider protocol that uses the PDF document as a file source.
 */
@interface PSPDFFileAnnotationProvider : NSObject <PSPDFAnnotationProvider>

/// Designated initializer.
- (id)initWithDocumentProvider:(PSPDFDocumentProvider *)documentProvider;

/// Associated documentProvider.
@property (nonatomic, weak) PSPDFDocumentProvider *documentProvider;

/// Default annotation username. Defaults to nil.
/// Written as the "T" (title/user) property of newly created annotations.
@property (atomic, copy) NSString *defaultAnnotationUsername;

/**
 Performance optimized access.

 The default implementation is lazy loaded (and of course thread safe); hitting a dictionary cache first and blocks if no cache is found. After the first expensive call, this method is basically free. Ensure that you're using a similar cache if you replace this method with your own.
*/
- (NSArray *)annotationsForPage:(NSUInteger)page pageRef:(CGPDFPageRef)pageRef;

/**
 You can add your own annotations (like videos, links) here.
 Note: Usually it's a better idea to implement a custom AnnotationProvider, but this is kept for backwards compatibility.

 You will override any already set annotations, so if you want to mix in annotations from the PDF, use addAnnotations:forPage: instead.
 Note: Setting nil as annotations will re-evaluate the pdf for annotations on the next access. Use an empty array if you want to clear annotations instead.
*/
- (void)setAnnotations:(NSArray *)annotations forPage:(NSUInteger)page;

/// Will add the annotation to the current annotation array. Will accept any annotations.
- (BOOL)addAnnotations:(NSArray *)annotations forPage:(NSUInteger)page;

/// Removes all annotation and re-evalutes the document on next access.
- (void)clearCache;

/// Try to load annotations from file and set them if successful.
- (BOOL)tryLoadAnnotationsFromFileWithError:(NSError **)error;

/// The fileType translation table is used when we encounter pspdfkit:// links.
/// Maps e.g. "mpg" to PSPDFLinkAnnotationVideo.
@property (nonatomic, copy) NSDictionary *fileTypeTranslationTable;

/// Change the protocol that's used to parse pspdfkit-additions (links, audio, video)
/// Defaults to 'pspdfkit://'.
@property (nonatomic, copy) NSString *protocolString;

/// Path where annotations are being saved if saving to external file is enabled.
/// Default's to self.documentProvider.document.cacheDirectory + "annotations_%d.pspdfkit" (%d = number of the documentProvider)
/// If set to nil, will revert back to the default value.
@property (nonatomic, copy) NSString *annotationsPath;

@end


@interface PSPDFFileAnnotationProvider (SubclassingHooks)

/// Parses the page annotation dictionary and returns the newly created annotations.
/// Want to customize annotations right after parsing? This is the perfect place.
/// Will be called from annotationsForPage:pageRef: in a thread safe manner and later cached.
- (NSArray *)parseAnnotationsForPage:(NSUInteger)page pageRef:(CGPDFPageRef)pageRef;

/// Saving code.
- (BOOL)saveAnnotationsWithError:(NSError **)error;

/// Load annotations (returning NO + eventually an error if it fails)
- (NSDictionary *)loadAnnotationsWithError:(NSError **)error;

/// Parses annotation link target. Override to support custom link protocols.
- (void)parseAnnotationLinkTarget:(PSPDFLinkAnnotation *)linkAnnotation;

/// Resolves a PSPDFKit-style URL to the appropriate NSURL.
+ (NSURL *)resolvePath:(NSString *)path forDocument:(PSPDFDocument *)document page:(NSUInteger)page;

/// filtered fileTypeTranslationTable that only returns video elements.
- (NSArray *)videoFileTypes;

/// Removes all annotations that are marked as deleted.
- (NSUInteger)removeDeletedAnnotations;

@end
