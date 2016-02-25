//
//  wkCBSManager.h
//  Pods
//
//  Created by apple on 14-9-15.
//  Core Beacon Shoper Manager, the SDK Caller interface
//

#import <Foundation/Foundation.h>

// 应用中的
@interface wkAppUser : NSObject
@property (nonatomic,strong) NSNumber* appuserid;
@property (nonatomic,strong) NSString* username;

- (wkAppUser*)initWithappUserid:(NSNumber*)userId   // 在系统中的会员id
                               vip:(BOOL)isVip
                               name:(NSString*)userName // 会员名
                             Gender:(NSString*)gender   // 性别
                                age:(NSNumber*)age      // 年龄
                           portrait:(NSString*)portrait  // 指向画像的路径
                        memberLevel:(NSString*)memberlevel // 会员等级
                        descirption:(NSString*)descirption; // 会员描述
@end

typedef enum
{
    WK_SDK_PUSH_COMMON,     //普通的PUSH，在进入CheckPoint，更新CheckPoint的时候获取
    WK_SDK_PUSH_WELCOME,    //欢迎Push，在CheckPoint CheckIn的时候获取显示
    WK_SDK_PUSH_BYE     //再见Push，在CheckPoint CheckOut的时候获取显示
}WK_SDK_PUSH_TYPE_E;


@interface wkSdkBeaconShow : NSObject
@property (nonatomic, readwrite, strong) NSString* title;//show 的名称
@property (nonatomic, readwrite, strong) NSString* content;//show的内容
@property (nonatomic, readwrite, strong) NSString* iconUrl;//当前Show的Icon图标路径
@property (nonatomic, readwrite, strong) NSString* url;//显示时指向的url
@property (nonatomic, readwrite, strong) NSString* urlContentType;
//显示时指向的url的类型:1. Promotion(优惠券) 2.PromotionList(优惠券列表) 3.ImageAd(图片广告) 4.(视频广告)
@property (nonatomic, readwrite, strong) NSString* parameter;//参数信息
@property (nonatomic, readwrite) CGFloat cdistant;//当前位置到beacon的距离
@end

@interface wkSdkPush : NSObject
@property (nonatomic, readwrite, strong) NSString* title;//Push的标题
@property (nonatomic, readwrite, strong) NSString* content;//Push的内容
@property (nonatomic, readwrite, strong) NSString* iconurl;//当前Push的Icon图标路径
@property (nonatomic, readwrite) WK_SDK_PUSH_TYPE_E type;//当前push的类型,该类型为枚举类型
@property (nonatomic, readwrite) NSString* urlType;
//显示时指向的url的类型:1. Promotion(优惠券) 2.PromotionList(优惠券列表) 3.ImageAd(图片广告) 4.(视频广告)
@property (nonatomic, readwrite, strong) NSString* url;//网页跳转路径,只有在isAction为true的时候有效
@end

@interface wkSdkCurrentArea : NSObject
@property (nonatomic, strong) NSString* positionId;//当前beacon的唯一id
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
 当用户登陆账号的时候，绑定应用用户的信息，从而帮助
 */
-(void)bindAppUser:(wkAppUser*)appuser
        withResponse:(void(^)(BOOL success, NSError* error))response;

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

/*获取当前的BeaconShow信息*/
- (wkSdkBeaconShow*)getCurrentBeaconShow;

/*获取当前的所在区域的信息*/
- (wkSdkCurrentArea*)getCurrentArea;
/*设置当前用户的群组信息*/
- (void)setUserTagInfo:(NSString*)info;
/*设置当前的DEBUG模式*/
- (void)setDeBugMode:(BOOL)isDebug;
/*启动当前的定位的WebView*/
- (void)startLocationWebView:(UINavigationController *)navi withCarNo:(NSString*)carNo;
@end

@protocol wkCBSManagerDelegate <NSObject>
@optional
-(void) beaconShowCallBack:(wkSdkBeaconShow*) beaconShow;
-(void) beaconPushCallBack:(wkSdkPush*) push;
-(void) beaconCheckInCallBack:(wkSdkCurrentArea*)area;
-(void) beaconCheckOutCallBack:(wkSdkCurrentArea*)area;
@end
