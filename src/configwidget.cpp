/*
grSim - RoboCup Small Size Soccer Robots Simulator
Copyright (C) 2011, Parsian Robotic Center (eew.aut.ac.ir/~parsian/grsim)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "configwidget.h"

#include <memory>

#define ADD_ENUM(type,name,Defaultvalue,namestring) \
    v_##name = std::shared_ptr<Var##type>(new Var##type(namestring,Defaultvalue));
#define ADD_VALUE(parent,type,name,defaultvalue,namestring) \
    v_##name = std::shared_ptr<Var##type>(new Var##type(namestring,defaultvalue)); \
    (parent)->addChild(v_##name);

#define END_ENUM(parents, name) \
    parents->addChild(v_##name);
#define ADD_TO_ENUM(name,str) \
    v_##name->addItem(str);


ConfigWidget::ConfigWidget()
{      
  tmodel=new VarTreeModel();
  this->setModel(tmodel);  
  geo_vars = std::make_shared<VarList>("Geometry");
  world.push_back(geo_vars);  
  robot_settings = new QSettings;

  VarListPtr game_vars(new VarList("Game"));
  geo_vars->addChild(game_vars);
  ADD_ENUM(StringEnum, Division, "Division B", "Division")
  ADD_TO_ENUM(Division, "Division A");
  ADD_TO_ENUM(Division, "Division B");
  END_ENUM(game_vars, Division);
  ADD_VALUE(game_vars,Int, Robots_Count, 5, "Robots Count")
  VarListPtr fields_vars(new VarList("Field"));
  VarListPtr div_a_vars(new VarList("Division A"));
  VarListPtr div_b_vars(new VarList("Division B"));
  geo_vars->addChild(fields_vars);
  fields_vars->addChild(div_a_vars);
  fields_vars->addChild(div_b_vars);

  ADD_VALUE(div_a_vars, Double, DivA_Field_Line_Width,0.003,"Line Thickness")
  ADD_VALUE(div_a_vars, Double, DivA_Field_Length,1.50,"Length")
  ADD_VALUE(div_a_vars, Double, DivA_Field_Width,1.300,"Width")
  ADD_VALUE(div_a_vars, Double, DivA_Field_Rad,0.200,"Radius")
  ADD_VALUE(div_a_vars, Double, DivA_Field_Free_Kick,0.200,"Free Kick Distance From Defense Area")
  ADD_VALUE(div_a_vars, Double, DivA_Field_Penalty_Width,0.70,"Penalty width")
  ADD_VALUE(div_a_vars, Double, DivA_Field_Penalty_Depth,0.15,"Penalty depth")
  ADD_VALUE(div_a_vars, Double, DivA_Field_Penalty_Point,0.35,"Penalty point")
  ADD_VALUE(div_a_vars, Double, DivA_Field_Margin,0.3,"Margin")
  ADD_VALUE(div_a_vars, Double, DivA_Field_Referee_Margin,0.4,"Referee margin")
  ADD_VALUE(div_a_vars, Double, DivA_Wall_Thickness,0.025,"Wall thickness")
  ADD_VALUE(div_a_vars, Double, DivA_Goal_Thickness,0.025,"Goal thickness")
  ADD_VALUE(div_a_vars, Double, DivA_Goal_Depth,0.10,"Goal depth")
  ADD_VALUE(div_a_vars, Double, DivA_Goal_Width,0.40,"Goal width")
  ADD_VALUE(div_a_vars, Double, DivA_Goal_Height,0.05,"Goal height")

  ADD_VALUE(div_b_vars, Double, DivB_Field_Line_Width,0.003,"Line Thickness")
  ADD_VALUE(div_b_vars, Double, DivB_Field_Length,2.200,"Length")
  ADD_VALUE(div_b_vars, Double, DivB_Field_Width,1.800,"Width")
  ADD_VALUE(div_b_vars, Double, DivB_Field_Rad,0.25,"Radius")
  ADD_VALUE(div_b_vars, Double, DivB_Field_Free_Kick,0.25,"Free Kick Distance From Defense Area")
  ADD_VALUE(div_b_vars, Double, DivB_Field_Penalty_Width,0.800,"Penalty width")
  ADD_VALUE(div_b_vars, Double, DivB_Field_Penalty_Depth,0.35,"Penalty depth")
  ADD_VALUE(div_b_vars, Double, DivB_Field_Penalty_Point,0.375,"Penalty point")
  ADD_VALUE(div_b_vars, Double, DivB_Field_Margin,0.30,"Margin")
  ADD_VALUE(div_b_vars, Double, DivB_Field_Referee_Margin,0.4,"Referee margin")
  ADD_VALUE(div_b_vars, Double, DivB_Wall_Thickness,0.025,"Wall thickness")
  ADD_VALUE(div_b_vars, Double, DivB_Goal_Thickness,0.025,"Goal thickness")
  ADD_VALUE(div_b_vars, Double, DivB_Goal_Depth,0.150,"Goal depth")
  ADD_VALUE(div_b_vars, Double, DivB_Goal_Width,0.40,"Goal width")
  ADD_VALUE(div_b_vars, Double, DivB_Goal_Height,0.05,"Goal height")

  ADD_ENUM(StringEnum,YellowTeam,"Parsian","Yellow Team");
  END_ENUM(geo_vars,YellowTeam)
  ADD_ENUM(StringEnum,BlueTeam,"Parsian","Blue Team");
  END_ENUM(geo_vars,BlueTeam)

    VarListPtr ballg_vars(new VarList("Ball"));
    geo_vars->addChild(ballg_vars);
        ADD_VALUE(ballg_vars,Double,BallRadius,0.0215,"Radius")
  VarListPtr phys_vars(new VarList("Physics"));
  world.push_back(phys_vars);
    VarListPtr worldp_vars(new VarList("World"));
    phys_vars->addChild(worldp_vars);  
        ADD_VALUE(worldp_vars,Double,DesiredFPS,60,"Desired FPS")
        ADD_VALUE(worldp_vars,Bool,SyncWithGL,false,"Synchronize ODE with OpenGL")
        ADD_VALUE(worldp_vars, Bool, SyncWithPython, false, "Synchronize SimStep with python " )
        ADD_VALUE(worldp_vars,Double,DeltaTime,0.016,"ODE time step")
        ADD_VALUE(worldp_vars,Double,Gravity,9.8,"Gravity")
        ADD_VALUE(worldp_vars,Bool,ResetTurnOver,true,"Auto reset turn-over")
  VarListPtr ballp_vars(new VarList("Ball"));
    phys_vars->addChild(ballp_vars);
        ADD_VALUE(ballp_vars,Double,BallMass,0.043,"Ball mass");
        ADD_VALUE(ballp_vars,Double,BallFriction,0.05,"Ball-ground friction")
        ADD_VALUE(ballp_vars,Double,BallSlip,1,"Ball-ground slip")
        ADD_VALUE(ballp_vars,Double,BallBounce,0.5,"Ball-ground bounce factor")
        ADD_VALUE(ballp_vars,Double,BallBounceVel,0.1,"Ball-ground bounce min velocity")
        ADD_VALUE(ballp_vars,Double,BallLinearDamp,0.004,"Ball linear damping")
        ADD_VALUE(ballp_vars,Double,BallAngularDamp,0.004,"Ball angular damping")
  VarListPtr comm_vars(new VarList("Communication"));
  world.push_back(comm_vars);
    ADD_VALUE(comm_vars,String,VisionMulticastAddr,"224.0.0.1","Vision multicast address")  //LocalHost
    ADD_VALUE(comm_vars,Int,VisionMulticastPort,10002,"Vision multicast port")
    ADD_VALUE(comm_vars,Int,CommandListenPort,20011,"Command listen port")
    ADD_VALUE(comm_vars,Int,BlueStatusSendPort,30011,"Blue Team status send port")
    ADD_VALUE(comm_vars,Int,YellowStatusSendPort,30012,"Yellow Team status send port")
    ADD_VALUE(comm_vars,Int,sendDelay,0,"Sending delay (milliseconds)")
    ADD_VALUE(comm_vars,Int,sendGeometryEvery,120,"Send geometry every X frames")
    VarListPtr gauss_vars(new VarList("Gaussian noise"));
        comm_vars->addChild(gauss_vars);
        ADD_VALUE(gauss_vars,Bool,noise,false,"Noise")
        ADD_VALUE(gauss_vars,Double,noiseDeviation_x,3,"Deviation for x values")
        ADD_VALUE(gauss_vars,Double,noiseDeviation_y,3,"Deviation for y values")
        ADD_VALUE(gauss_vars,Double,noiseDeviation_angle,2,"Deviation for angle values")
    VarListPtr vanishing_vars(new VarList("Vanishing probability"));
        comm_vars->addChild(vanishing_vars);
        ADD_VALUE(gauss_vars,Bool,vanishing,false,"Vanishing")
        ADD_VALUE(vanishing_vars,Double,blue_team_vanishing,0,"Blue team")
        ADD_VALUE(vanishing_vars,Double,yellow_team_vanishing,0,"Yellow team")
        ADD_VALUE(vanishing_vars,Double,ball_vanishing,0,"Ball")


    QDir dir;
    std::string blueteam = v_BlueTeam->getString();
    geo_vars->removeChild(v_BlueTeam);

    std::string yellowteam = v_YellowTeam->getString();
    geo_vars->removeChild(v_YellowTeam);

    ADD_ENUM(StringEnum,BlueTeam,blueteam,"Blue Team");
    ADD_ENUM(StringEnum,YellowTeam,yellowteam,"Yellow Team");

    QDir::setCurrent(qApp->applicationDirPath()+"/../config/");
    dir.setNameFilters(QStringList() << "*.ini");
    dir.setSorting(QDir::Size | QDir::Reversed);
    QFileInfoList list = dir.entryInfoList();
    for (const auto& fileInfo : list) {
        QStringList s = fileInfo.fileName().split(".");
        QString str;
        if (s.count() > 0) str = s[0];
        ADD_TO_ENUM(BlueTeam,str.toStdString())
        ADD_TO_ENUM(YellowTeam,str.toStdString())
    }
    QDir::setCurrent(qApp->applicationDirPath()+"/../share/grsim/config/");
    dir.setNameFilters(QStringList() << "*.ini");
    dir.setSorting(QDir::Size | QDir::Reversed);
    list = dir.entryInfoList();
    for (const auto& fileInfo : list) {
        QStringList s = fileInfo.fileName().split(".");
        QString str;
        if (s.count() > 0) str = s[0];
        ADD_TO_ENUM(BlueTeam,str.toStdString())
        ADD_TO_ENUM(YellowTeam,str.toStdString())
    }

    END_ENUM(geo_vars,BlueTeam)
    END_ENUM(geo_vars,YellowTeam)

  v_BlueTeam->setString(blueteam);
  v_YellowTeam->setString(yellowteam);

  tmodel->setRootItems(world);

  this->expandAndFocus(geo_vars);
  this->expandAndFocus(phys_vars);
  this->expandAndFocus(comm_vars);

  this->fitColumns();

  resize(320,400);
  connect(v_BlueTeam.get(), SIGNAL(wasEdited(VarPtr)), this, SLOT(loadRobotsSettings()));
  connect(v_YellowTeam.get(), SIGNAL(wasEdited(VarPtr)), this, SLOT(loadRobotsSettings()));
  loadRobotsSettings();
}

ConfigWidget::~ConfigWidget() {  
   VarXML::write(world,(QDir::homePath() + QString("/.grsim.xml")).toStdString());
}


ConfigDockWidget::ConfigDockWidget(QWidget* _parent,ConfigWidget* _conf){
    parent=_parent;conf=_conf;
    setWidget(conf);
    conf->move(0,20);
}  
void ConfigDockWidget::closeEvent(QCloseEvent* event)
{
    emit closeSignal(false);
}


void ConfigWidget::loadRobotsSettings()
{
    loadRobotSettings(YellowTeam().c_str());
    yellowSettings = robotSettings;
    loadRobotSettings(BlueTeam().c_str());
    blueSettings = robotSettings;
}

void ConfigWidget::loadRobotSettings(const QString&& team)
{
    QString ss = qApp->applicationDirPath()+QString("/../config/")+QString("%1.ini").arg(team);
    robot_settings = new QSettings(ss, QSettings::IniFormat);
    robotSettings.RobotCenterFromKicker = robot_settings->value("Geometery/CenterFromKicker", 0.073).toDouble();
    robotSettings.RobotRadius = robot_settings->value("Geometery/Radius", 0.09).toDouble();
    robotSettings.RobotHeight = robot_settings->value("Geometery/Height", 0.13).toDouble();
    robotSettings.BottomHeight = robot_settings->value("Geometery/RobotBottomZValue", 0.02).toDouble();
    robotSettings.WheelRadius = robot_settings->value("Geometery/WheelRadius", 0.0325).toDouble();
    robotSettings.WheelThickness = robot_settings->value("Geometery/WheelThickness", 0.005).toDouble();
    robotSettings.Wheel1Angle = robot_settings->value("Geometery/Wheel1Angle", 60).toDouble();
    robotSettings.Wheel2Angle = robot_settings->value("Geometery/Wheel2Angle", 135).toDouble();
    robotSettings.BallRadius = robot_settings->value("Geometery/BallRadius", 0.002).toDouble();
    robotSettings.BallMass = robot_settings->value("Geometery/BallMass", 0.001).toDouble();

    robotSettings.BodyMass  = robot_settings->value("Physics/BodyMass", 2).toDouble();
    robotSettings.WheelMass = robot_settings->value("Physics/WheelMass", 0.2).toDouble();
    robotSettings.WheelTangentFriction = robot_settings->value("Physics/WheelTangentFriction", 0.8f).toDouble();
    robotSettings.WheelPerpendicularFriction = robot_settings->value("Physics/WheelPerpendicularFriction", 0.05f).toDouble();
    robotSettings.Wheel_Motor_FMax = robot_settings->value("Physics/WheelMotorMaximumApplyingTorque", 0.2f).toDouble();
}
