//
//  NGAudioPlayer.h
//  NGAudioPlayer
//
//  Created by Matthias Tretter on 21.06.12.
//  Copyright (c) 2012 NOUS Wissensmanagement GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "NGAudioPlayerPlaybackState.h"
#import "NGAudioPlayerDelegate.h"
#import "NSURL+NGAudioPlayerNowPlayingInfo.h"
#import <CoreMedia/CoreMedia.h>
#import <AVFoundation/AVFoundation.h>

@interface NGAudioPlayer : NSObject

@property (nonatomic, weak) id<NGAudioPlayerDelegate> delegate;
@property (nonatomic, readonly, getter = isPlaying) BOOL playing;
@property (nonatomic, readonly) NGAudioPlayerPlaybackState playbackState;

@property (nonatomic, readonly) NSURL *currentPlayingURL;
@property (nonatomic, readonly) NSTimeInterval durationOfCurrentPlayingURL;
@property (nonatomic, readonly) NSArray *enqueuedURLs;

@property (nonatomic, readonly) AVPlayerItem *currentItem;

/** Automatically updates MPNowPlayingInfoCenter with the dictionary associated with a given NSURL, defaults to YES */
@property (nonatomic, assign) BOOL automaticallyUpdateNowPlayingInfoCenter;

/** if set, stops the player at this specific date (e.g. to use for a timer like in tvs etc.), also works if the app is in background */
@property (nonatomic, strong) NSDate *stopDate;

/** if YES, starts an observation block and calls delegates didChangeTime method */
@property (nonatomic, readwrite) BOOL useDidChangeTimeObservation;

/** if YES, player will try to play the currentItem again when it failed to play to end, defaults to YES */
@property (nonatomic, assign, getter=shouldRetry) BOOL retryEnabled;

/******************************************
 @name Class Methods
 ******************************************/

+ (BOOL)setAudioSessionCategory:(NSString *)audioSessionCategory;
+ (BOOL)initBackgroundAudio;

/******************************************
 @name Lifecycle
 ******************************************/

- (id)initWithURL:(NSURL *)url;
- (id)initWithURLs:(NSArray *)urls;

/******************************************
 @name Playback
 ******************************************/

/**
 This method removes all items from the queue and starts playing the given URL.
 
 @param url the URL to play
 */
- (void)playURL:(NSURL *)url;
- (void)play;
- (void)pause;
/**
 Pauses the player and removes all items from the queue.
 */
- (void)stop;
- (void)togglePlayback;

- (void)fadePlayerFromVolume:(CGFloat)fromVolume toVolume:(CGFloat)toVolume duration:(NSTimeInterval)duration;

- (void)seekCurrentItemToPositionInPercent:(float)percentTime;

/******************************************
 @name Queuing
 ******************************************/

/**
 This method adds the given URL to the end of the queue.
 
 @param url the URL to add to the queue
 @return YES if the URL was added successfully, NO otherwise
 */
- (BOOL)enqueueURL:(NSURL *)url;

/**
 This method adds the given URLs to the end of the queue.
 
 @param urls the URLs to add to the queue
 @return YES if all URLs were added successfully, NO otherwise
 */
- (BOOL)enqueueURLs:(NSArray *)urls;

/******************************************
 @name Removing
 ******************************************/

/**
 Removes the item with the given URL from the player-queue.
 
 @param url the URL of the item to remove
 @return YES if an item was removed, NO otherwise
 */
- (BOOL)removeURL:(NSURL *)url;
- (void)removeAllURLs;

- (void)advanceToNextURL;

@end

///////////////////////////////////////////////////////////////////////////
#pragma mark - Subclassing Hooks
///////////////////////////////////////////////////////////////////////////

@interface NGAudioPlayer (SubclassingHooks)

- (void)handleRateChange:(NSDictionary *)change;
- (void)handlePlaybackBufferChange:(NSDictionary *)change;
- (void)handleStatusChange:(NSDictionary *)change;
- (void)handleCurrentItemChange:(NSDictionary *)change;
- (void)playerItemDidPlayToEndTime:(NSNotification *)notification;
- (void)handlePlayerItemTimedMetadataChange:(NSDictionary *)change object:(id)object;

@end
