## First half is code for model 1, model 2, log model 2
library(ggplot2)
library(car)

lsts <- read.csv("/Users/NhiVo/Desktop/ECS 132 FinalProject/listings.csv")

dropFeatures = function(frame) {
  lsts_col = names(frame)
  
  #drop all url's from frame
  frame = frame[,-grep("*url*", lsts_col)]
  
  #consider using indicator for experiences_offered for none or not
  text_feature_names = c("summary", "space", "description", "experiences_offered",
                         "neighborhood_overview", "notes", "transit", "access",
                         "interaction", "house_rules", "host_name", "host_about",
                         "amenities", "license", "host_verifications")
  
  location = c("host_location", "street", "city", "state", "zipcode",
               "market", "smart_location", "country_code", "country",
               "latitude", "longitude", "is_location_exact", "jurisdiction_name")
  
  dates = c("first_review", "host_since", "last_review", "calendar_last_scraped",
            "calendar_updated")
  
  additional = c("id", "scrape_id", "last_scraped", "name", "host_id",
                 "host_response_time", "host_is_super_host",
                 "weekly_price", "monthly_price", "host_acceptance_rate",
                 "property_type", "has_availability",
                 "is_business_travel_ready")
  
  frame = frame[, !names(frame) %in% text_feature_names]
  frame = frame[, !names(frame) %in% location]
  frame = frame[, !names(frame) %in% dates]
  frame = frame[, !names(frame) %in% additional]
  return(frame)
}

#converts dollar amounts to numeric
cleanCurrency = function(frame) {
  currCol = c("price", "cleaning_fee", "extra_people")
  for (col in currCol) {
    frame[, col] <- as.numeric(gsub('[$,]', '', frame[, col]))
  }
  return(frame)
}


lsts = dropFeatures(lsts)
lsts = cleanCurrency(lsts)

#remove '%' in host_response rate to numeric
lsts$host_response_rate = as.numeric(sub("%", "",lsts$host_response_rate))

#lsts$host_is_superhost from 't' and 'f' to '1' and '0'
lsts$host_is_superhost <- as.integer(lsts$host_is_superhost=='t') 

#lsts$host_has_profile_pic from 't' and 'f' to '1' and '0'
lsts$host_has_profile_pic <- as.integer(lsts$host_has_profile_pic=='t') 

#lsts$host_has_profile_pic from 't' and 'f' to '1' and '0'
lsts$host_identity_verified <- as.integer(lsts$host_identity_verified=='t')

#lsts$roomtype = (1) Entire home/apt (2)Private room (3)Private room 
lsts$room_type <- as.integer(lsts$room_type==1 | lsts$room_type==2 | lsts$room_type==3)

#lsts$bedtype = (1) Airbed (2) Couch (3) Futon (4) Pull-out Sofa (5) Real Bed
lsts$bed_type <- as.integer(lsts$bed_type==1 | lsts$bed_type==2 | lsts$bed_type==3 | lsts$bed_type==4 | lsts$bed_type==5)

#lsts$requires_license from 't' and 'f' to '1' and '0'
lsts$requires_license <- as.integer(lsts$requires_license=='t')

#lsts$instant_bookable from 't' and 'f' to '1' and '0'
lsts$instant_bookable <- as.integer(lsts$instant_bookable=='t')

#lsts$cancellation_policy = (1) flexible (2) moderate (3) strict (4) strict_14_with_grace_period (5) super_strict_30 (6) super_strit_60
lsts$cancellation_policy <- as.integer(lsts$cancellation_policy==1 | lsts$cancellation_policy==2 | lsts$cancellation_policy==3 | lsts$cancellation_policy==4 | lsts$cancellation_policy==5 | lsts$cancellation_policy==6)

#lsts$require_guest_phone_verification from 't' and 'f' to '1' and '0'
lsts$require_guest_phone_verification <- as.integer(lsts$require_guest_phone_verification=='t')

#lsts[is.na(lsts)] <- 0

#### model 1#####
### predicting pricefrom all other variables ###
set.seed(9999)
idxs <- sample(1:nrow(lsts),1000)
tstdta <- lsts[idxs,]
trndta <- lsts[-idxs,]
lmout <- lm(price ~ .,data=trndta,na.action=na.exclude)
plot(lmout,col='paleturquoise3')

summary(lmout,na.action=na.exclude) 
confint(lmout)
predvals <- predict(lmout,tstdta[,-14],na.action=na.exclude)
mean(abs(predvals-tstdta[,14]))    


#### model 2#####
sqft0 <- lsts$square_feet
sqft0 <- sqft[!is.na(sqft)]
sqft <- lsts$square_feet
sqft[is.na(sqft)] <- median(sqft0)

df <- lsts[,c(9,10,16,1)]
df$sqft <- sqft
df$sqft2 <- sqft^2
df$sqft3 <- sqft^3
df$price <- lsts$price
set.seed(9999)
idxs <- sample(1:nrow(df),1000)
tstdta <- df[idxs,]
trndta <- df[-idxs,]
lmout <- lm(price ~ .,data=trndta,na.action=na.exclude)
plot(lmout,col='paleturquoise3')

summary(lmout,na.action=na.exclude)   ##   , R^2 = .1178
confint(lmout) 
predvals <- predict(lmout,tstdta[,-8],na.action=na.exclude)
mean(abs(predvals-tstdta[,8])) ## $146.9813

pfout <- polyFit(trndta,deg=2) 
mean(abs(predict(pfout,trndta[,-8]) - trndta[,8]))  $126.2231
pfout <- polyFit(trndta,deg=3)     #deg 3 best model
mean(abs(predict(pfout,trndta[,-8]) - trndta[,8]))   $126.1809


#### model  log price#####
sqft0 <- lsts$square_feet
sqft0 <- sqft[!is.na(sqft)]
sqft <- lsts$square_feet
sqft[is.na(sqft)] <- median(sqft0)
hostrsp_sqft <- lsts$host_response_rate*sqft

df2 <- lsts[,c(9,10,16,1)]
df2$sqft <- sqft
df2$sqft2 <- sqft^2
df2$sqft3 <- sqft^3
df$hostrsp_sqft <- hostrsp_sqft
df2$price <- log(lsts$price)
set.seed(9999)
idxs <- sample(1:nrow(df2),1000)
tstdta <- df2[idxs,]
trndta <- df2[-idxs,]
lmout <- lm(price ~ .,data=trndta,na.action=na.exclude)
plot(lmout,main='log price',col='paleturquoise3')

summary(lmout,na.action=na.exclude)   ##   , R^2 = .3359
confint(lmout) 
predvals <- predict(lmout,tstdta[,-8],na.action=na.exclude)
mean(abs(predvals-tstdta[,8]))    


df <- NULL
df2 <- NULL




#### Second half code for model 3 ###

library(ggplot2)

lsts <- read.csv("/Users/jacobmorris/Downloads/listings.csv")

dropFeatures = function(frame) {
  lsts_col = names(frame)
  
  #drop all url's from frame
  frame = frame[,-grep("*url*", lsts_col)]
  
  #consider using indicator for experiences_offered for none or not
  text_feature_names = c("summary", "space", "description", "experiences_offered",
                         "neighborhood_overview", "notes", "transit", "access",
                         "interaction", "house_rules", "host_name", "host_about",
                         "amenities", "license", "host_verifications")
  
  location = c("host_location", "street", "city", "state", "zipcode",
               "market", "smart_location", "country_code", "country",
               "latitude", "longitude", "is_location_exact", "jurisdiction_name")
  
  dates = c("first_review", "host_since", "last_review", "calendar_last_scraped",
            "calendar_updated")
  
  additional = c("id", "scrape_id", "last_scraped", "name", "host_id",
                 "host_response_time", "host_is_super_host",
                 "weekly_price", "monthly_price", "host_acceptance_rate",
                 "property_type", "has_availability",
                 "is_business_travel_ready", "square_feet",
                 "host_has_profile_pic", "calculated_host_listings_count_shared_rooms")
  
  reviews = c("review_scores_rating", "review_scores_cleanliness", "review_scores_checkin",
              "review_scores_communication", "review_scores_location",
              "review_scores_value", "host_total_listings_count")
  
  
  
  
  frame = frame[, !names(frame) %in% text_feature_names]
  frame = frame[, !names(frame) %in% location]
  frame = frame[, !names(frame) %in% dates]
  frame = frame[, !names(frame) %in% additional]
  frame = frame[, !names(frame) %in% reviews]
  return(frame)
}

#converts dollar amounts to numeric
cleanCurrency = function(frame) {
  currCol = c("price", "cleaning_fee", "extra_people")
  for (col in currCol) {
    frame[, col] <- as.numeric(gsub('[$,]', '', frame[, col]))
  }
  return(frame)
}


lsts = dropFeatures(lsts)
lsts = cleanCurrency(lsts)

#remove '%' in host_response rate to numeric
lsts$host_response_rate = as.numeric(sub("%", "",lsts$host_response_rate))

#lsts$host_is_superhost from 't' and 'f' to '1' and '0'
lsts$host_is_superhost <- as.integer(lsts$host_is_superhost=='t') 

#lsts$host_has_profile_pic from 't' and 'f' to '1' and '0'
lsts$host_has_profile_pic <- as.integer(lsts$host_has_profile_pic=='t') 

#lsts$host_has_profile_pic from 't' and 'f' to '1' and '0'
lsts$host_identity_verified <- as.integer(lsts$host_identity_verified=='t')

#lsts$roomtype = (1) Entire home/apt (2)Private room (3)Shared room 
#shared room will be case of all other indicators being 0
room_type <- as.integer(lsts$room_type)
lsts$entire <- as.integer(room_type==1)
lsts$private <- as.integer(room_type==2)
lsts$room_type = NULL

#lsts$bedtype = (1) Airbed (2) Couch (3) Futon (4) Pull-out Sofa (5) Real Bed
#real bed will be case of all other indicators being 0
bed_type <- as.integer(lsts$bed_type)
lsts$airbed <- as.integer(bed_type==1)
lsts$couch <- as.integer(bed_type==2)
lsts$futon <- as.integer(bed_type==3)
lsts$pulloutsofa <- as.integer(bed_type==4)
lsts$bed_type = NULL

#lsts$requires_license from 't' and 'f' to '1' and '0'
lsts$requires_license <- as.integer(lsts$requires_license=='t')

#lsts$instant_bookable from 't' and 'f' to '1' and '0'
lsts$instant_bookable <- as.integer(lsts$instant_bookable=='t')

#lsts$cancellation_policy = (1) flexible (2) moderate (3) strict (4) strict_14_with_grace_period (5) super_strict_30 (6) super_strit_60
#strict will be case of all other indicators being 0
cancellation_policy <- as.integer(lsts$cancellation_policy)
lsts$flexible <- as.integer(cancellation_policy==1)
lsts$moderate <- as.integer(cancellation_policy==2)
#lsts$strict <- as.integer(cancellation_policy==3 | cancellation_policy==4 | cancellation_policy==5 | cancellation_policy==6)
#lsts$strict_14_with_grace_period <- as.integer(cancellation_policy==4)
#lsts$super_strict_30 <- as.integer(cancellation_policy==5)
#lsts$super_strict_60 <- as.integer(cancellation_policy==6)
lsts$cancellation_policy = NULL
#lsts$require_guest_phone_verification from 't' and 'f' to '1' and '0'
lsts$require_guest_phone_verification <- as.integer(lsts$require_guest_phone_verification=='t')


#handle 'NA' values
lsts$host_response_rate[is.na(lsts$host_response_rate)] = median(lsts$host_response_rate, na.rm = T)
lsts$beds[is.na(lsts$beds)] = median(lsts$beds, na.rm = T)
lsts$bedrooms[is.na(lsts$bedrooms)] = median(lsts$bedrooms, na.rm = T)
lsts$bathrooms[is.na(lsts$bathrooms)] = median(lsts$bathrooms, na.rm = T)
lsts$cleaning_fee[is.na(lsts$cleaning_fee)] = mean(lsts$cleaning_fee, na.rm = T)
lsts$reviews_per_month[is.na(lsts$reviews_per_month)] = median(lsts$reviews_per_month, na.rm = T)

set.seed(9999)

idxs <- sample(1:nrow(lsts),1000)
tstdta <- lsts[idxs,]
trndta <- lsts[-idxs,]

#predict 
lm_model1 <- lm(price ~ bathrooms + bedrooms + beds + entire + private +
                + flexible + moderate
                + calculated_host_listings_count
                + extra_people + cleaning_fee + accommodates,
                data=trndta,na.action=na.exclude)
#lm_model1 <- lm(price ~ bathrooms + bedrooms + beds + cleaning_fee
#                + reviews_per_month + number_of_reviews
#                + guests_included + entire + private +
#                + flexible + moderate
#                + airbed + couch + futon + pulloutsofa,data=trndta,na.action=na.exclude)
plot(lm_model1,col='paleturquoise3')
#abline(lm_model1)
summary(lm_model1)      
prediction <- predict(lm_model1, newdata =  tstdta[c(1:8, 10:ncol(trndta))])
#performance
difference = abs(prediction - tstdta["price"])
#average price difference
sapply(difference, mean)
