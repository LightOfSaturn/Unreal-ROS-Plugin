#pragma once

#include "ROS_TEST.h"
#include "TopicTemplate.h"
#include <string>
#include <rapidjson/document.h>
#include <rapidjson/rapidjson.h>
#include "ros_msg_test.generated.h"

{% for Struct in StructList%}
struct  F{{Struct.name}};
{% endfor %}


{% for Struct in StructList%}
{% set TypeName = Struct.name %}
{% set TypeNameFull = Struct.namefull %}
{% set Props = Struct.props %}
USTRUCT()
struct F{{TypeName}}
{

	GENERATED_USTRUCT_BODY()

    {% for item in Props:%}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Robot OS")
	{% if item.type in Primitivelist %}
	{{Primitivelist[item.type] }} {{ item.name }};
	{% else %}
	F{{UserTypeList[item.type].name}} {{ item.name }};
	{% endif %}
    {% endfor %}

	rapidjson::Value Serialization(rapidjson::Document & d);
	void Unserialization(rapidjson::Value & v);

	std::string TypeName = "{{TypeNameFull}}";

};


UCLASS()
class U{{TypeName}}Advertiser : public UAdvertiser
{

	GENERATED_UCLASS_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Robot OS")
	static U{{TypeName}}Advertiser * Create_{{TypeName}}_Advertiser(FString TopicName);

	UFUNCTION(BlueprintCallable, Category = "Robot OS")
	void Publish(F{{TypeName}} Data);
};

{% endfor %}
