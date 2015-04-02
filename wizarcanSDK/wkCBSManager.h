//
//  wkCBSManager.h
//  Pods
//
//  Created by apple on 14-9-15.
//  Core Beacon Shoper Manager, the SDK Caller interface
//

#import <Foundation/Foundation.h>

@interface wkCBSBeaconInfo : NSObject
@property (nonatomic, readwrite, strong) NSString* uuid;//Push的标题
@property (nonatomic, readwrite) uint16_t major;//Push的标题
@property (nonatomic, readwrite) uint16_t minor;//Push的标题
@end

@protocol wkCBSManagerDelegate;

/**
 Core Beacon Shop Manager, 是应用集成CoreBeaconShop的直接调用类，SDK中所有的调用接口都直接
 */
@interface wkCBSManager : NSObject

@property(nonatomic, assign) id<wkCBSManagerDelegate> delegate;


/**
 返回缺省的Manager，通过该函数获取当前系统的Manager
 */
+(wkCBSManager*)defaultManager;

/**
 设置开发账号以及密钥，开发者账号和密钥通过注册获得，必须首先设置正确的
 开发者账号和密钥才能实现相关的功能。
 */
-(void)setDevAccount:(NSString*)account     // 开发者账号
              andKey:(NSString*)key;        // 开发者密钥
/**
 在AppDelegate的applicationDidEnterForeground:中调用该函数，保证
 SDK在background下能共工作正常。 该函数必须调用
 */
- (void)applicationDidEnterForeground;
/**
 在AppDelegate的applicationDidEnterBackground:中调用该函数，保证
 SDK在background下能共工作正常。 该函数必须调用
 */
- (void)applicationDidEnterBackground;
//设置checkin的有效距离
- (void)setCheckInRange:(float)range;
@end

@protocol wkCBSManagerDelegate <NSObject>
@optional
-(void) beaconCheckInCallBack:(wkCBSBeaconInfo*)beacon;
-(void) beaconCheckOutCallBack:(wkCBSBeaconInfo*)beacon;
@end

