//
//  NGAudioPlayerPlaybackState.h
//  NGAudioPlayer
//
//  Created by Matthias Tretter on 21.06.12.
//  Copyright (c) 2012 NOUS Wissensmanagement GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, NGAudioPlayerPlaybackState) {
    NGAudioPlayerPlaybackStatePlaying = 0,
    NGAudioPlayerPlaybackStatePaused,
    NGAudioPlayerPlaybackStateBuffering,
    NGAudioPlayerPlaybackStateFailed
};